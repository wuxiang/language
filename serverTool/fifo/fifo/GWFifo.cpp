#include "GWFifo.h"

GWFifo::GWFifo(const char* name, const int& length):  m_length(length), m_tag(MAX_TAG_NUM), m_tag_array(NULL)
{
	if (length > 255)
	{
		printf("%s(%d): file name is too long!\n", __FILE__, __LINE__);
		exit(-1);
	}

	bzero(&m_name, 255);
	strncpy(m_name, name, length);

	// init all tag  by tag info
	m_tag_array = new TagST*[m_tag];
	bzero(m_tag_array, m_tag * sizeof(TagST*));

	for (int i = 0; i < m_tag; ++i)
	{
		m_tag_array[i] = new TagST();
	}
}

GWFifo::~GWFifo()
{
	//m_tag_array;
	for (int i = 0; i < m_tag; ++i)
	{
		delete m_tag_array[i];
	}

	delete []m_tag_array;
}

bool GWFifo::set(int tag, void* obj, int len)
{
	bool flag = false;
	{
		// shared mutex
		GW_shared_lock   lock(m_mtx);
		if (tag >= m_tag)
		{
			flag = true;
		}
	}

	if (flag)
	{
		// upgrade lock
		GW_unique_lock   lock(m_mtx);

		TagST**   tmptr = new TagST*[2 * m_tag];
		for (int i = 0; i < m_tag; ++i)
		{
			tmptr[i] = m_tag_array[i];
			m_tag_array[i] = NULL;
		}

		for (int i = m_tag; i < 2 * m_tag; ++i)
		{
			m_tag_array[i] = new TagST();
		}

		m_tag *= 2;

		delete []m_tag_array;

		m_tag_array = tmptr;
	}

	{
		// shared mutex
		GW_shared_lock   lock(m_mtx);

		if (m_tag_array[tag]->tInfo == NULL)
		{
			GW_lock_guard  guard(m_tag_array[tag]->tLock);
			if (m_tag_array[tag]->tInfo == NULL)
			{
				m_tag_array[tag]->tInfo = new TagInfo(m_name, m_length, tag);
			}
		}

		return m_tag_array[tag]->tInfo->set(obj, len);
	}
}

bool  GWFifo::get(int tag, void* obj, int* len)
{
	// shared mutex
	GW_shared_lock   lock(m_mtx);
	if (tag >= m_tag)
	{
		len = 0;
		return false;
	}

	if (m_tag_array[tag]->tInfo == NULL)
	{
		GW_lock_guard  guard(m_tag_array[tag]->tLock);
		if (m_tag_array[tag]->tInfo == NULL)
		{
			m_tag_array[tag]->tInfo = new TagInfo(m_name, m_length, tag);
		}
	}

	return m_tag_array[tag]->tInfo->get(obj, len);

	//return tag;
}

