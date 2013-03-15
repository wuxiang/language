#include "GWexecutor.h"
#include "GWDBfront.h"

//static void*  routine(void* pArg)
//{
//	MysqlThreadData   threadLocal;
//	pthread_exit((void*)0);
//}

GW_executor::GW_executor(const int num): m_run(false), m_th_num(num)
{
	m_th_id_ptr = new  pthread_t[m_th_num];
	bzero(m_th_id_ptr, m_th_num * sizeof(pthread_t));

	// mutex and cond only for thread waiting,
	// should not be used for protect other variable
	pthread_mutex_init(&m_unused_mtx, NULL);
	pthread_cond_init(&m_cond, NULL);
}

GW_executor::~GW_executor()
{
	{
		bool flag = false;
		{
			GW_lock_guard lock(m_mtx);
			if (m_run)
			{
				flag = true;
			}
		}

		if (flag)
		{
			stop();
		}
	}

	delete []m_th_id_ptr;

	pthread_mutex_destroy(&m_unused_mtx);
	pthread_cond_destroy(&m_cond);
}

void GW_executor::notify()
{
	if (0 != pthread_cond_broadcast(&m_cond))
	{
		fprintf(stderr, "%s(%d): nofify waiting thread failed!!!\n", __FILE__, __LINE__);
	}
}

void GW_executor::wait()
{
	pthread_mutex_lock(&m_unused_mtx);
	pthread_cond_wait(&m_cond, &m_unused_mtx);
	pthread_mutex_unlock(&m_unused_mtx);
}

bool GW_executor::is_runing()
{
	GW_lock_guard lock(m_mtx);
	return m_run;
}

void GW_executor::start(GW_DBfront*  front)
{
	{
		GW_lock_guard     lock(m_mtx);
		m_run = true;
	}

	for (int i = 0; i < m_th_num; ++i)
	{
		if (pthread_create(&m_th_id_ptr[i],  NULL, routine, front))
		{
			fprintf(stderr, "%s(%d): pthread_create failed !!!\n", __FILE__, __LINE__);
		}
	}
}

void GW_executor::stop()
{
	{
		GW_lock_guard  lock(m_mtx);
		m_run = false;
	}

	notify();

	for (int i = 0; i < m_th_num; ++i)
	{
		if (m_th_id_ptr[i] != 0)
		{
			pthread_join(m_th_id_ptr[i], NULL);
		}
	}
}

