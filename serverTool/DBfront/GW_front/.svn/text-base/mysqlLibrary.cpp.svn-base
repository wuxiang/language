#include "mysqlLibrary.h"

MysqlLibrary::MysqlLibrary()
{
	GW_lock_guard     lock(m_mtx);
	if (mysql_library_init(0, NULL, NULL))
	{
		fprintf(stderr, "%s(%d): init mysql library failed!!!", __FILE__, __LINE__);
	}
}

MysqlLibrary::~MysqlLibrary()
{
	GW_lock_guard     lock(m_mtx);
	mysql_library_end();
}

