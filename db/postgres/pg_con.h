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
    //{host, port user, passwd, dbname}
    //for a sake of extend
    pg_con(const char** key, const char** value);
    ~pg_con();
    bool close();

private:
    bool parse_option(const char** key, const char** value);
    bool connect_sync(const char** key, const char** value);

private:
    PGconn*    m_ptrPG;
    std::string   m_host;
    std::string   m_port;
    std::string   m_user;
    std::string   m_passwd;
    std::string   m_dbName;
};

#endif //_PG_CON_H_
