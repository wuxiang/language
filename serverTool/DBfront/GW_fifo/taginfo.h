#ifndef _TAGINFO_H_
#define _TAGINFO_H_
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

class TagInfo
{
public:
	TagInfo(const char* const fileName, const int& length, const int tag);
	~TagInfo();

	bool set(void* obj, int len);
	bool  get(void* obj, int* len);

private:
	bool  initStatus(const char* const fileName);
	bool  intToChar(int src, char*  des);
	int   charToInt(const char*  src);
	bool  commit_or_not();

private:
	const int		 m_self;
	time_t        m_time;

	GW_spin_lock     m_mtx;
	OffsetInfo*      m_offset_ptr;
	char*			 m_start_ptr;
	char*			 m_end_ptr;

private:
	int		INTSIZE;
	char*   m_get_ptr;
	char*   m_put_ptr;
};

#endif //_TAGINFO_H_
