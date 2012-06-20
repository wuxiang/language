#include "pg_con.h"

pg_con::pg_con(const char** key, const char** value): m_ptrPG(NULL)
{
    if (!parse_option(key, value))
    {
        printf("\033[22;31m %s: %d (parse_option failed) \033[0m \n", __FILE__, __LINE__);
    }

    if (!connect_sync(key, value))
    {
        printf("\033[22;31m %s: %d (connect to postgres server failed) \033[0m \n", __FILE__, __LINE__);
        close();
    }
}

pg_con::~pg_con()
{
    close();
}

bool pg_con::close()
{
    if (m_ptrPG)
    {
        PQfinish(m_ptrPG);
        m_ptrPG = NULL;
    }

    return true;
}

bool pg_con::connect_sync(const char** key, const char** value)
{

    m_ptrPG = PQconnectdbParams(key, value, 1);

    if (!m_ptrPG || (PQstatus(m_ptrPG) != CONNECTION_OK))
    {
        return false;
    }

    return true;
}

bool pg_con::parse_option(const char** key, const char** value)
{
    const char**  pkey = key;
    const char**  pvalue = value;
    int size_key = 0;
    int size_value = 0;

    for (; (pkey != NULL) || (pvalue != NULL);  ++pkey, ++pvalue)
    {
        //whether size of key and sizeof value equal?
        if (pkey != NULL)
        {
            ++size_key;
        }

        if (pvalue != NULL)
        {
            ++size_value;
        }

        if ( size_key != size_value)
        {
            return false;
        }

        //store value
        if (!strcmp(*pkey, "host"))
        {
            m_host = pvalue[size_value - 1];
        }
        else if (!strcmp(*pkey, "port"))
        {
            m_port = pvalue[size_value - 1];
        }
        else if (!strcmp(*pkey, "user"))
        {
            m_user = pvalue[size_value - 1];
        }
        else if (!strcmp(*pkey, "passwd"))
        {
            m_passwd = pvalue[size_value - 1];
        }
        else if (!strcmp(*pkey, "dbname"))
        {
            m_dbName = pvalue[size_value - 1];
        }
        else
        {
            return false;
        }
    }
    return true;
}
