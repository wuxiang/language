#include "sqlHandle.h"

sqlHandle::sqlHandle(const db_config&   config): m_config(config), m_db_ptr(NULL)
{
	db_connect(config);
}

sqlHandle::~sqlHandle()
{
	db_disconnect();
}

bool sqlHandle::db_connect(const db_config&   config)
{
	GW_lock_guard     lock(m_mtx);
	if (!(m_db_ptr = mysql_init(NULL)))
	{
		fprintf(stderr, "%s(%d): MYSQL init failed!!!\n", __FILE__, __LINE__);
		return false;
	}
	else
	{
		if (!mysql_real_connect(m_db_ptr, config.host, config.user, config.pass,
					config.dbName, config.port, config.socketName, config.flag))
		{
			fprintf(stderr, "%s(%d): connect to mysql failed!!!\n", __FILE__, __LINE__);
			return false;
		}
	}

	return true;
}

bool sqlHandle::db_disconnect()
{
	GW_lock_guard     lock(m_mtx);
	if (m_db_ptr)
	{
		mysql_close(m_db_ptr);
	}

	return true;
}

int sqlHandle::sql_query(const char* stmt_str)
{
	GW_lock_guard     lock(m_mtx);
	return mysql_query(m_db_ptr, stmt_str);
}

const char* sqlHandle::sql_error()
{
	return mysql_error(m_db_ptr);
}

