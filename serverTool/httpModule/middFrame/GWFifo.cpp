#include "GWFifo.h"

GWFifo::GWFifo()
{
}

GWFifo::GWFifo(const GWFifo& ff)
{
}

GWFifo::~GWFifo()
{
}

bool GWFifo::push(HttpReqMsg*  req);
{
	GW_unique_lock  lock(m_mtx);
	m_deqt.push_back(req);
	return true;
}

HttpReqMsg*  GWFifo::getFront()
{
	GW_shared_lock  lock(m_mtx);
	if (m_deqt.empty())
	{
		return NULL;
	}

	return m_deqt.front();
}

bool  GWFifo::popFront()
{
	GW_unique_lock lock(m_mtx);
	m_deqt.pop_front();
	return true;
}

bool  GWFifo::is_empty()
{
	GW_shared_lock  lock(m_mtx);
	return  m_deqt.empty();
}

