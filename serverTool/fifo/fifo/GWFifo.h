#ifndef _FIFO_H_
#define _FIFO_H_
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "taginfo.h"
#include "GWconstant.h"
#include "GWMutex.h"

class GWFifo
{
private:
	struct   TagST
	{
		TagST(): tInfo(NULL)
		{
		}

		~TagST()
		{
			delete tInfo;
		}


		GW_spin_lock  tLock;
		TagInfo*   tInfo;
	};

public:
	// each GWFifo has a file, so we need user
	// offer a different name, and length <=255
	GWFifo(const char* name, const int& length);
	~GWFifo();

	bool set(int tag, void* obj, int len);
	bool  get(int tag, void* obj, int* len);
	//int  get(int tag, void* obj, int* len);

private:
	GWFifo(const GWFifo&);
	GWFifo operator=(const GWFifo&);

private:
	int             m_length;
	char			m_name[255]; // file name

	GW_shared_mutex m_mtx;
	int             m_tag;
	TagST**    	m_tag_array;
};

#endif //_FIFO_H_

