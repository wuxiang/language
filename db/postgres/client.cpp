#include <iostream>
#include <libpq-fe.h>
#include "pg_con.h"

int main()
{
    const char*  key[6] = {"hostaddr", "port", "user", "password", "dbname", NULL};
    const char*  value[6] = {"192.168.1.54", "5432", "order", "order", "mydb", NULL};

    pg_con   pg(key, value);
    return 0;
}
