#include "pg_con.h"

pg_con::pg_con(const char** key, const char** value): m_ptrPG(NULL), m_result(NULL)
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

void pg_con::reset()
{
    PQreset(m_ptrPG);
}

void pg_con::dump_server_info()
{
    printf("=========================postgreSQL info======================\n");
    printf("database name of connection: %s\n", PQdb(m_ptrPG));
    printf("username of connection: %s\n", PQuser(m_ptrPG));
    printf("connection status: %d\n", PQstatus(m_ptrPG));
    printf("transaction status: %d\n", PQtransactionStatus(m_ptrPG));
    printf("protocol version: %d\n", PQprotocolVersion(m_ptrPG));
    printf("serversion version: %d\n", PQserverVersion(m_ptrPG));
    printf("======================end postgreSQL info=====================\n");
}

bool pg_con::connect_sync(const char** key, const char** value)
{

    m_ptrPG = PQconnectdbParams(key, value, 0);
    //m_ptrPG = PQsetdbLogin(m_host.c_str(), m_port.c_str(), NULL, NULL, m_dbName.c_str(), m_user.c_str(), m_passwd.c_str());

    if (!m_ptrPG || (PQstatus(m_ptrPG) != CONNECTION_OK))
    {
        printf("error::%s\n", PQerrorMessage(m_ptrPG));
        return false;
    }

    printf("connect postgreSQL success!\n");

    return true;
}

bool pg_con::parse_option(const char** key, const char** value)
{
    const char**  pkey = key;
    const char**  pvalue = value;
    int size_key = 0;
    int size_value = 0;

    for (; (*pkey != NULL) || (*pvalue != NULL);  ++pkey, ++pvalue)
    {
        //whether size of key and sizeof value equal?
        if (*pkey != NULL)
        {
            ++size_key;
        }

        if (*pvalue != NULL)
        {
            ++size_value;
        }

        if ( size_key != size_value)
        {
            return false;
        }

        //store value
        if (!strcmp(*pkey, "hostaddr"))
        {
            m_host = *pvalue;
        }
        else if (!strcmp(*pkey, "port"))
        {
            m_port = *pvalue;
        }
        else if (!strcmp(*pkey, "user"))
        {
            m_user = *pvalue;
        }
        else if (!strcmp(*pkey, "password"))
        {
            m_passwd = *pvalue;
        }
        else if (!strcmp(*pkey, "dbname"))
        {
            m_dbName = *pvalue;
        }
        else
        {
            return false;
        }
    }

    return true;
}

//transaction
void pg_con::transaction_begin()
{
    m_result = PQexec(m_ptrPG, "begin");

    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
    }
}

void pg_con::transaction_end()
{
    m_result = PQexec(m_ptrPG, "commit");

    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "commit transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
    }
}

void pg_con::transaction_rooback()
{
    m_result = PQexec(m_ptrPG, "rollback");

    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "rollback transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
    }
}

bool pg_con::create_table()
{
    m_result = PQexec(m_ptrPG, "begin");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " create table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }
    PQclear(m_result);

    m_result = PQexec(m_ptrPG, "create table first( \
                                time  date,\
                                writer varchar(10)\
                                )");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " create table failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    m_result = PQexec(m_ptrPG, "commit");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " create table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    PQclear(m_result);
    return true;
}

bool pg_con::drop_table(const char* tbName)
{
    m_result = PQexec(m_ptrPG, "begin");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " drop table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }
    PQclear(m_result);

    m_result = PQexec(m_ptrPG, "drop table first");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " drop table failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    m_result = PQexec(m_ptrPG, "commit");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " drop table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    PQclear(m_result);
    return true;
}

//insert
bool pg_con::insert(const std::string& writer, const std::string& date)
{
    //transaction begin
    m_result = PQexec(m_ptrPG, "begin");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " insert table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    std::string  command = "insert into first(time,writer) values($1, $2)";
    const char* value[] = {date.c_str(), writer.c_str()};
    const int length[] = {date.length(), writer.length()};
    const int format[] = {0, 0};
    m_result = PQexecParams(m_ptrPG, command.c_str(), 2, NULL, value, length, format, 0);
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " insert table failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }


    //transaction end
    m_result = PQexec(m_ptrPG, "commit");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " insert table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    PQclear(m_result);
    return true;
}

//del
bool pg_con::delete_table()
{
    return true;
}

//update
bool pg_con::update(const std::string& writer)
{
    return true;
}

//query
bool pg_con::select()
{
    //transaction begin
    m_result = PQexec(m_ptrPG, "begin");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " select table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    m_result = PQexec(m_ptrPG, "select * from first");
    if (PQresultStatus(m_result) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, " select failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    int rows = PQntuples(m_result);
    int columns = PQnfields(m_result);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            fprintf(stderr, "%s\t", PQgetvalue(m_result, i, j));
        }
        fprintf(stderr, "\n");
    }

    //transaction end
    m_result = PQexec(m_ptrPG, "commit");
    if (PQresultStatus(m_result) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, " select table, transaction failed: %s\n", PQerrorMessage(m_ptrPG));
        PQclear(m_result);
        reset();
        return false;
    }

    PQclear(m_result);
    return true;
}

