#ifndef _GWDBFRONT_H_
#define _GWDBFRONT_H_
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "GWexecutor.h"
#include "sqlHandle.h"
#include "GWFifo.h"
#include "stForMysql.h"
#include "mysqlLibrary.h"

extern void*  routine(void* pArg);

class GW_DBfront
{
public:
	GW_DBfront(const char* name, const db_config&  config, const int w_thread_background = 2, const int tag = DEFAULT_FRONT_TAG);

	// here is interface for user
	bool start();
	bool put(const char* sql);
	bool get(const char* sql, void* Data, int* len);
	bool status(sqlInfo& info);

	// below is used for thread background
	bool commitN_inc();
	bool doneN_inc();
	bool errN_inc(const int errCode, const char*  sql);

	friend void*  routine(void* pArg);

private:
	int             m_tag;
	sqlInfo         m_info;
	GWFifo          m_fifo;
	sqlHandle       m_sql;
	GW_executor     m_executor;
	int             m_fd;
};

extern  MysqlLibrary     single;

#endif //_GWDBFRONT_H_
