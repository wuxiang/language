#ifndef _FIFO_H_
#define _FIFO_H_
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

#include <deque>

#include "GWMutex.h"
#include "HttpMsg.h"

class GWFifo
{
public:
	GWFifo();
	~GWFifo();

	bool push(HttpReqMsg*  req);
	HttpReqMsg*  getFront();
	HttpReqMsg*  getAndPopFront();
	bool  popFront();

	bool  is_empty();

private:
	GWFifo(const GWFifo&);
	GWFifo operator=(const GWFifo&);


private:
	GW_shared_mutex     m_mtx;
	std::deque<HttpReqMsg*>  m_deqt;
};

#endif //_FIFO_H_

