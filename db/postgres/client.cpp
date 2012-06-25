#include <iostream>
#include <libpq-fe.h>
#include "pg_con.h"

int main()
{
    const char*  key[6] = {"hostaddr", "port", "user", "password", "dbname", NULL};
    const char*  value[6] = {"192.168.1.76", "5432", "order", "order", "mydb", NULL};

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
