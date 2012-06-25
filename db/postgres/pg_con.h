#ifndef _PG_CON_H_
#define _PG_CON_H_
#include <boost/noncopyable.hpp>
#include <string>
#include <libpq-fe.h>

#include <string.h>
#include <stdio.h>

class pg_con: private boost::noncopyable
{
public:
    //now here support for serval key;
    //{host, port user, password, dbname}
    //for a sake of extend
    pg_con(const char** key, const char** value);
    ~pg_con();
    bool close();

    //transaction observice
    void transaction_begin();
    void transaction_end();
    void transaction_rooback();

    //manager table in database
    bool create_table();
    bool drop_table(const char* tbName);

    //operator in table level below
    //insert
    bool insert(const std::string& writer, const std::string& date);
    
    //del
    bool delete_table();
    
    //update
    bool update(const std::string& writer);

    //query
    bool select();


private:
    bool parse_option(const char** key, const char** value);
    bool connect_sync(const char** key, const char** value);
    void dump_server_info();
    void reset();

private:
    PGconn*    m_ptrPG;
    PGresult*  m_result;
    std::string   m_host;
    std::string   m_port;
    std::string   m_user;
    std::string   m_passwd;
    std::string   m_dbName;
};

#endif //_PG_CON_H_
