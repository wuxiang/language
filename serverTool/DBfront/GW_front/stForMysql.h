#ifndef _STFORMYSQL_H_
#define _STFORMYSQL_H_
#include <string.h>

const int   DEFAULT_FRONT_TAG = 0;

struct  sqlInfo
{
	size_t  commit_num;
	size_t  done_num;
	size_t  err_num;

	sqlInfo(): commit_num(0), done_num(0), err_num(0)
	{
	}
};

struct db_config
{
	char   host[255];
	char   user[255];
	char   pass[255];
	char   dbName[255];
	unsigned int  port;
	char*         socketName;
	unsigned long  flag;

	db_config(): port(0), socketName(NULL), flag(0)
	{
		bzero(host, 255);
		bzero(user, 255);
		bzero(pass, 255);
		bzero(dbName, 255);
	}

	~db_config()
	{
		if (!socketName)
		{
			delete []socketName;
		}
	}

	db_config(const db_config&   config): port(config.port), flag(config.flag)
	{
		bzero(host, 255);
		strcpy(host, config.host);

		bzero(user, 255);
		strcpy(user, config.user);

		bzero(pass, 255);
		strcpy(pass, config.pass);

		bzero(dbName, 255);
		strcpy(dbName, config.dbName);

		if (config.socketName)
		{
			socketName = new char[strlen(config.socketName) + 1];
			bzero(socketName, strlen(config.socketName) + 1);
			strcpy(socketName, config.socketName);
		}
		else
		{
			socketName = NULL;
		}
	}

	db_config&  operator=(const db_config& config)
	{
		bzero(host, 255);
		strcpy(host, config.host);

		bzero(user, 255);
		strcpy(user, config.user);

		bzero(pass, 255);
		strcpy(pass, config.pass);

		bzero(dbName, 255);
		strcpy(dbName, config.dbName);

		port = config.port;

		if (config.socketName)
		{
			socketName = new char[strlen(config.socketName) + 1];
			bzero(socketName, strlen(config.socketName) + 1);
			strcpy(socketName, config.socketName);
		}
		else
		{
			socketName = NULL;
		}

		flag = config.flag;

		return *this;
	}
};

#endif //_STFORMYSQL_H_
