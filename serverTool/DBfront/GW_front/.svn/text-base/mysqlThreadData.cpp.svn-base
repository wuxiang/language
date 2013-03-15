#include "mysqlThreadData.h"

MysqlThreadData::MysqlThreadData()
{
	if (mysql_thread_init() != 0)
	{
		fprintf(stderr, "%s(%d): mysql_thread_init failed!!!\n", __FILE__, __LINE__);
	}
}

MysqlThreadData::~MysqlThreadData()
{
	mysql_thread_end();
}

