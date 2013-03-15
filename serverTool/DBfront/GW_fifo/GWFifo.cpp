#include "GWFifo.h"

GWFifo::GWFifo(const char* name, const int& length): INTSIZE(sizeof(int))
{
	if (length > 255)
	{
		printf("%s(%d): file name is too long!\n", __FILE__, __LINE__);
		exit(-1);
	}

	 m_offset_ptr = NULL;
	 m_start_ptr = NULL;
	 m_end_ptr = NULL;

	 m_get_ptr = NULL;
	 m_put_ptr = NULL;

	// set tag file status
	if (!initStatus(name))
	{
		exit(-1);
	}

	// set alerm  star time
	time(&m_time);

}

bool GWFifo::initStatus(const char* const fileName)
{
	int fd = 0;
	size_t  SFile = 0;

	// make judgement of file exist
	bool flag = (-1 == access(fileName, F_OK));

	if (-1 == (fd = open(fileName, O_RDWR|O_CREAT, S_IRWXU)))
	{
		printf("%s(%d): open file failed!\n", __FILE__, __LINE__);
		close(fd);
		return false;
	}

	// set file size
	if (flag)
	{
		if (-1 == ftruncate(fd, INIT_FILE_SIZE))
		{
			printf("%s(%d): resize file size failed!\n", __FILE__, __LINE__);
			close(fd);
			return false;
		}

		SFile = INIT_FILE_SIZE;
	}
	else
	{
		struct stat st;
		memset(&st, 0, sizeof(st));
		fstat(fd, &st);
		SFile = st.st_size;
	}

	// mmap file to virtual memory
	m_offset_ptr = (OffsetInfo*)mmap(NULL, SFile, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (m_offset_ptr == MAP_FAILED)
	{
		printf("%s(%d): mmap file to memory  failed!\n", __FILE__, __LINE__);
		close(fd);
		return false;
	}

	m_start_ptr = (char*)((int)m_offset_ptr + sizeof(struct OffsetInfo));

	if (flag)
	{
		bzero(m_offset_ptr, sizeof(struct OffsetInfo));
	}

	m_offset_ptr->size = INIT_FILE_SIZE - sizeof(struct OffsetInfo);
	m_end_ptr = m_start_ptr + m_offset_ptr->size;
	m_get_ptr = m_start_ptr + m_offset_ptr->iget;
	m_put_ptr = m_start_ptr + m_offset_ptr->iput;

	close(fd);

	return true;
}

GWFifo::~GWFifo()
{
	if (-1 == msync((void*)m_offset_ptr, INIT_FILE_SIZE, MS_SYNC))
	{
		printf("%s(%d)  commit failed in TagInfo deconstruct!!!\n", __FILE__, __LINE__);
	}

	//printf("(*m_offset_ptr).iused = %d\n", (*m_offset_ptr).iused);
	//printf("(*m_offset_ptr).iget = %d\n", (*m_offset_ptr).iget);
	//printf("(*m_offset_ptr).iput = %d\n", (*m_offset_ptr).iput);
	//printf("(*m_offset_ptr).size = %d\n", (*m_offset_ptr).size);
	munmap((void*)m_offset_ptr, INIT_FILE_SIZE);
}

bool  GWFifo::intToChar(int src, char*  des)
{
	for (int i = 0; i < INTSIZE; ++i)
	{
		des[i] = ((src >> (i * 8)) & 0xff);
	}

	return true;
}

int   GWFifo::charToInt(const char*  src)
{
	int res = 0;
	for (int i = 0; i < INTSIZE; ++i)
	{
		res = res | (((int)(src[i]) << (i * 8)) & ((int)(0xff) << (i * 8)));
	}

	return res;
}

bool GWFifo::set(int tag, void* obj, int len)
{
	GW_unique_lock    lock(m_mtx);
	if (m_offset_ptr->iused + len + 2 * INTSIZE > m_offset_ptr->size)
	{
		// resize file size
		printf("fifo is full\n");
		return false;
	}
	else
	{

		char  pTag[255] = {};
		intToChar(tag, pTag);
		for (int i = 0; i < INTSIZE; ++i)
		{
			if (m_put_ptr == m_end_ptr)
			{
				m_put_ptr = m_start_ptr;
			}

			*m_put_ptr++ = pTag[i];
		}

		char  tmp[255] = {};
		intToChar(len, tmp);

		for (int i = 0; i < INTSIZE; ++i)
		{
			if (m_put_ptr == m_end_ptr)
			{
				m_put_ptr = m_start_ptr;
			}

			*m_put_ptr++ = tmp[i];
		}

		char* cntPtr = (char*)obj;
		for (int i = 0; i < len; ++i)
		{
			if (m_put_ptr == m_end_ptr)
			{
				m_put_ptr = m_start_ptr;
			}

			*m_put_ptr++ = cntPtr[i];
		}

		int off = m_offset_ptr->iput + 2 * INTSIZE + len;
		m_offset_ptr->iput =  off % m_offset_ptr->size;
		m_offset_ptr->iused += (2 * INTSIZE + len);

	}

	if (!commit_or_not())
	{
		printf("%s(%d)  commit failed!!!\n", __FILE__, __LINE__);
	}

	return true;
}

bool  GWFifo::get(int* tag, void* obj, int* len)
{
	if (obj == NULL)
	{
		return false;
	}

	GW_unique_lock    lock(m_mtx);
	if (m_offset_ptr->iused > 0)
	{
		char* tmpGetPtr = m_get_ptr;

		// tag
		char  pTag[255] = {};
		for (int i = 0 ; i < INTSIZE; ++i)
		{
			if (tmpGetPtr == m_end_ptr)
			{
				tmpGetPtr = m_start_ptr;
			}

			pTag[i] = *tmpGetPtr++;
		}
		*tag = charToInt(pTag);

		// len
		char  tmp[255] = {};
		for (int i = 0 ; i < INTSIZE; ++i)
		{
			if (tmpGetPtr == m_end_ptr)
			{
				tmpGetPtr = m_start_ptr;
			}

			tmp[i] = *tmpGetPtr++;
		}
		int si = charToInt(tmp);
		if (si > *len)
		{
			*len = si;
			return false;
		}
		else
		{
			m_get_ptr = tmpGetPtr;
			*len = si;
		}

		// obj
		char*  ptr = (char*)obj;
		for (int i = 0; i < *len; ++i)
		{
			if (m_get_ptr == m_end_ptr)
			{
				m_get_ptr = m_start_ptr;
			}

			ptr[i] = *m_get_ptr++;
		}

		m_offset_ptr->iused -= (2 * INTSIZE + *len);
		int off = m_offset_ptr->iget + 2 * INTSIZE + *len;
		m_offset_ptr->iget =  off % m_offset_ptr->size;
	}
	else
	{
		printf("buffer is empty!!!\n");
		return false;
	}

	if (!commit_or_not())
	{
		printf("%s(%d)  commit failed!!!\n", __FILE__, __LINE__);
	}

	return true;
}

bool  GWFifo::commit_or_not()
{
	time_t  tmpTime;
	time(&tmpTime);
	if (tmpTime - m_time >= COMMIT_PERIOD_TIME)
	{
		if (-1 == msync((void*)m_offset_ptr, INIT_FILE_SIZE, MS_SYNC))
		{
			return false;
		}

		m_time = tmpTime;
	}

	return true;
}

bool  GWFifo::is_empty()
{
	GW_shared_lock    lock(m_mtx);
	if (m_offset_ptr->iused <= 0)
	{
		return true;
	}

	return false;
}

