#include "GWDBfront.h"

MysqlLibrary     single;

void*  routine(void* pArg)
{
	GW_DBfront*   handle = (GW_DBfront*)pArg;
	if (!handle)
	{
		fprintf(stderr, "%s(%d): cast arguement failed when start thread!!!", __FILE__, __LINE__);
		pthread_exit((void*)0);
	}


	MysqlThreadData   threadLocal;

	int     size = 1024; /*used for store data*/
	char*   pData = new char[size];

	int tag = -1;
	int realSize = size;

	while (handle->m_executor.is_runing())
	{
		// init  argurment
		bzero(pData, size);
		tag = -1;
		realSize = size;

		if (!handle->m_fifo.get(&tag, pData, &realSize))
		{
			if (realSize > size)
			{
				delete []pData;
				size *= 2;
				pData = new char[size];
			}
			else if(pData && (tag == -1) && (realSize == size))
			{
				handle->m_executor.wait();
			}
			else if (!pData)
			{
				pData = new char[size];
			}
			else
			{
				fprintf(stderr, "%s(%d): unknown error happen here", __FILE__, __LINE__);
			}

			continue;
		}

		int res = handle->m_sql.sql_query(pData);

		if (res != 0)
		{
			fprintf(stderr, "%s(%d): write to mysql failed\nerror code: %d\n%s!!!\n", __FILE__, __LINE__, res, handle->m_sql.sql_error());
			handle->errN_inc(res, pData);

		}
		else
		{
			handle->doneN_inc();
		}
	}

	delete []pData;
	pthread_exit((void*)0);
}

GW_DBfront::GW_DBfront(const char* name, const db_config&  config, const int w_thread_background, const int tag)
					: m_tag(tag), m_fifo(name, strlen(name)), m_sql(config), m_executor(w_thread_background)
{
	// open file to write failed record
	char   filename[255];
	char*  pErr = "errorRecord";
	strcpy(filename, name);
	strcat(filename, pErr);

	if (-1 == (m_fd = open(filename, O_RDWR|O_CREAT, S_IRWXU)))
	{
		printf("%s(%d): open file failed!\n", __FILE__, __LINE__);
		close(m_fd);
	}
}

bool GW_DBfront::start()
{
	m_executor.start((GW_DBfront*)this);
	return true;
}

bool GW_DBfront::put(const char* sql)
{
	bool res = m_fifo.set(m_tag, (void*)sql, strlen(sql));

	if (res)
	{
		commitN_inc();
		m_executor.notify();
	}

	return res;
}

bool GW_DBfront::get(const char* sql, void* Data, int* len)
{
	return true;
}

bool GW_DBfront::status(sqlInfo& info)
{
	info = m_info;
	return true;
}


bool GW_DBfront::commitN_inc()
{
	__sync_fetch_and_add(&m_info.commit_num, 1);
	return true;
}

bool GW_DBfront::doneN_inc()
{
	__sync_fetch_and_add(&m_info.done_num, 1);
	return true;
}

bool GW_DBfront::errN_inc(const int errCode, const char*  sql)
{
	time_t   tm;
	time(&tm);
	char* pTm = ctime(&tm);

	char errC[255] = {};
	snprintf(errC, sizeof(errC), "::%d::", errCode);

	__sync_fetch_and_add(&m_info.err_num, 1);
	write(m_fd, pTm, strlen(pTm));
	write(m_fd, errC, strlen(errC));
	write(m_fd, sql, strlen(sql));
	write(m_fd, "\n", 1);
	return true;
}

