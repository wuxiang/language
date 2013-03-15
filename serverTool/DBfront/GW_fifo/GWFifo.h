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

#include "GWconstant.h"
#include "GW_st.h"
#include "GWMutex.h"

class GWFifo
{
public:
	// each GWFifo has a file, so we need user
	// offer a different name, and length <=255
	GWFifo(const char* name, const int& length);
	~GWFifo();

	bool set(int tag, void* obj, int len);
	bool  get(int* tag, void* obj, int* len);

	bool  is_empty();

private:
	bool  initStatus(const char* const fileName);
	bool  intToChar(int src, char*  des);
	int   charToInt(const char*  src);
	bool  commit_or_not();

private:
	GWFifo(const GWFifo&);
	GWFifo operator=(const GWFifo&);

private:
	time_t          m_time;


	GW_shared_mutex     m_mtx;
	OffsetInfo*      m_offset_ptr;
	char*			 m_start_ptr;
	char*			 m_end_ptr;

private:
	int		INTSIZE;
	char*   m_get_ptr;
	char*   m_put_ptr;
};

#endif //_FIFO_H_

