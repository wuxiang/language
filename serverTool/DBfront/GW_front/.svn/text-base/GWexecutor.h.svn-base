#ifndef _GWEXECUTOR_H_
#define _GWEXECUTOR_H_
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>

#include "mysqlThreadData.h"
#include "GWMutex.h"

class GW_DBfront;

//static void*  routine(void* pArg);

class GW_executor
{
public:
	GW_executor(const int num);
	~GW_executor();
	void start(GW_DBfront*  front);
	void stop();
	bool is_runing();
	void notify();
	void wait();

private:
	GW_executor(const GW_executor&);
	GW_executor operator=(const GW_executor&);

private:
	GW_spin_lock    m_mtx;
	bool            m_run;

	int             m_th_num;
	pthread_t*      m_th_id_ptr;

	// cause: used for free cpu, when  fifo is empty, and should not be used other place
	//		  should not be used for protecting other variable
	pthread_mutex_t    m_unused_mtx; /*only for thread waiting, when fifo is empty*/
	pthread_cond_t     m_cond;
};

#endif //_GWEXECUTOR_H_
