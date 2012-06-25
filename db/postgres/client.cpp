#include <iostream>
#include <stdio.h>

#include <ifaddrs.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <libpq-fe.h>

#include "pg_con.h"

std::string get_hostaddr_getnameinfo()
{
    struct ifaddrs* ifaddr = NULL;
    struct ifaddrs* ifa = NULL;
    int family = 0;
    int s = 0;
    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs failed\n");
        exit(EXIT_FAILURE);
    }

    char host[NI_MAXHOST] = {0};
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        family = ifa->ifa_addr->sa_family;
        printf("%s address family: %d%s\n", ifa->ifa_name, family,
                                            (family == AF_PACKET) ? " (AF_PACKET)" :
                                            (family == AF_INET) ?   " (AF_INET)" :
                                            (family == AF_INET6) ?  " (AF_INET6)" : "");

        if ((family == AF_INET || family == AF_INET6) && !(ifa->ifa_flags & IFF_LOOPBACK) && (ifa->ifa_flags & IFF_UP))
        {
            s = getnameinfo(ifa->ifa_addr, (family == AF_INET ? sizeof(struct sockaddr_in): sizeof(struct sockaddr_in6)), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0)
            {
                perror("getifaddrs failed\n");
                exit(EXIT_FAILURE);
            }
            printf("host: %s\n", host);
            freeifaddrs(ifaddr);
            return host;
        }
    }

    return std::string();
}

std::string get_hostaddr_inet_ntop()
{
    struct ifaddrs* ifaddr = NULL;
    struct ifaddrs* ifa = NULL;
    int family = 0;
    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs failed\n");
        exit(EXIT_FAILURE);
    }

    bool inet = false;
    void*  param = NULL;
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        family = ifa->ifa_addr->sa_family;
        printf("%s address family: %d%s\n", ifa->ifa_name, family,
                                            (family == AF_PACKET) ? " (AF_PACKET)" :
                                            (family == AF_INET) ?   " (AF_INET)" :
                                            (family == AF_INET6) ?  " (AF_INET6)" : "");

        if ((family == AF_INET || family == AF_INET6) && !(ifa->ifa_flags & IFF_LOOPBACK) && (ifa->ifa_flags & IFF_UP))
        {
            inet = (family == AF_INET ? true : false);
            //param = (void*)((inet ? (struct sockaddr_in* ) : (struct sockaddr_in6*))ifa->ifa_addr)->(inet ? sin_addr : sin6_addr);
            if (inet)
            {
                param = (void*)(&(((struct sockaddr_in*)ifa->ifa_addr)->sin_addr));
                char host[INET_ADDRSTRLEN] = {0};
                inet_ntop(AF_INET, param, host, INET_ADDRSTRLEN);
                printf("%s ip address: %s\n", ifa->ifa_name, host);
                freeifaddrs(ifaddr);
                return host;
            }
            else
            {
                param = (void*)(&(((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr));
                char host[INET6_ADDRSTRLEN] = {0};
                inet_ntop(AF_INET6, param, host, INET6_ADDRSTRLEN);
                printf("%s ip address: %s\n", ifa->ifa_name, host);
                freeifaddrs(ifaddr);
                return host;
            }
        }
    }

    return std::string();
}

int main()
{
    std::string addr = get_hostaddr_getnameinfo();
    //get_hostaddr_inet_ntop();
    const char*  key[6] = {"hostaddr", "port", "user", "password", "dbname", NULL};
    const char*  value[6] = {addr.c_str(), "5432", "order", "order", "mydb", NULL};

    pg_con   pg(key, value);
    pg.create_table();
    printf("begin insert\n");
    pg.insert("wuxiang", "2012-06-25");
    printf("end insert\n");

    printf("begin select\n");
    pg.select();
    printf("end select\n");
    return 0;
}
