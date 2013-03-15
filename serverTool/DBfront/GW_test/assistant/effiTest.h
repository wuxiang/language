#ifndef _EFFITEST_H_
#define _EFFITEST_H_
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "GWFifo.h"
#include "stForTest.h"

const int recordN = 1000000;

struct  th_arg
{
	int  type;
	void*   st;
};

class timeObj
{
public:
	timeObj(const char* timer)
	{
		bzero(val, 255);
		strcpy(val, timer);
		bzero(&start, sizeof(struct timeval));
		gettimeofday(&start, NULL);
	}

	~timeObj()
	{
		struct timeval end;
		bzero(&end, sizeof(struct timeval));
		gettimeofday(&end, NULL);
		printf("%s living time: %ld\n", val, ( end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
	}

private:
	char  val[255];
	struct  timeval   start;
};

//friend void* w_routine(void* ptr);
//friend void* r_routine(void* ptr);

class  EffiTest
{
public:
	EffiTest(const int num, const char* filename);
	~EffiTest();
	void runsingle_w();
	void runsingle_r();
	void runRdWr();
	void run();

	friend void* w_routine(void* ptr);
	friend void* r_routine(void* ptr);

private:
	int m_th_num;
	GWFifo       fifo;
	pthread_t*   m_pthread_w;
	pthread_t*   m_pthread_r;
	char*        m_filename;

};

extern EffiTest EffTest;

#endif //_EFFITEST_H_
