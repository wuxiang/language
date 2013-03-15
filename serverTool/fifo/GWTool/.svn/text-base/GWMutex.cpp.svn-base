#include "GWMutex.h"


GW_mutex::GW_mutex()
{
	int const res = pthread_mutex_init(&m_mutex, NULL);

	if (res)
	{
		printf("%s(%d):pthread_mutex_init  init mutex  failed!\n", __FILE__, __LINE__);
		exit(-1);
	}
}

GW_mutex::~GW_mutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void GW_mutex::lock()
{
	pthread_mutex_lock(&m_mutex);
}

void GW_mutex::unlock()
{
	pthread_mutex_unlock(&m_mutex);
}

bool GW_mutex::try_lock()
{
	int const res = pthread_mutex_trylock(&m_mutex);
	return !res;
}

/*********************************************
 * *
 * *GW_spin_lock
 * *
 * ******************************************/

GW_spin_lock::GW_spin_lock()
{
	int const res = pthread_spin_init(&m_mutex, 0);

	if (res)
	{
		printf("%s(%d):pthread_spin_init  init spin  failed!\n", __FILE__, __LINE__);
		exit(-1);
	}
}

GW_spin_lock::~GW_spin_lock()
{
	pthread_spin_destroy(&m_mutex);
}

void GW_spin_lock::lock()
{
	pthread_spin_lock(&m_mutex);
}

void GW_spin_lock::unlock()
{
	pthread_spin_unlock(&m_mutex);
}

bool GW_spin_lock::try_lock()
{
	int const res = pthread_spin_trylock(&m_mutex);
	return !res;
}

/*********************************************
 * *
 * *GW_shared_mutex
 * *
 * ******************************************/

GW_shared_mutex::GW_shared_mutex()
{
	int const res = pthread_rwlock_init(&m_mutex, NULL);

	if (res)
	{
		printf("%s(%d):pthread_rwlock_init  init rwlock  failed!\n", __FILE__, __LINE__);
		exit(-1);
	}
}

GW_shared_mutex::~GW_shared_mutex()
{
	pthread_rwlock_destroy(&m_mutex);
}

void GW_shared_mutex::rdlock()
{
	pthread_rwlock_rdlock(&m_mutex);
}

void GW_shared_mutex::wrlock()
{
	pthread_rwlock_wrlock(&m_mutex);
}

bool GW_shared_mutex::try_rdlock()
{
	int res = pthread_rwlock_tryrdlock(&m_mutex);
	if (0 == res)
	{
		return true;
	}
	//else if (EBUSY == res)
	//{
	//	return false;
	//}
	//else
	//{
	//	printf("%s:(%d) can't  lock rwlock!!!\n", __FILE__,  __LINE__);
	//}

	return false;
}

bool GW_shared_mutex::try_wrlock()
{
	int res = pthread_rwlock_trywrlock(&m_mutex);
	if (0 == res)
	{
		return true;
	}
	//else if (EBUSY == res)
	//{
	//	return false;
	//}
	//else
	//{
	//	printf("%s:(%d) can't  lock rwlock!!!\n", __FILE__,  __LINE__);
	//}

	return false;
}

void GW_shared_mutex::unlock()
{
	pthread_rwlock_unlock(&m_mutex);
}


/*********************************************
 * *
 * *GW_lock_guard
 * *
 * ******************************************/

GW_lock_guard::GW_lock_guard(GW_mutex& mtx): m_mutex(mtx)
{
	m_mutex.lock();
}

GW_lock_guard::GW_lock_guard(GW_spin_lock& mtx): m_mutex(mtx)
{
	m_mutex.lock();
}

GW_lock_guard::~GW_lock_guard()
{
	m_mutex.unlock();
}


/*********************************************
 * *
 * *GW_shared_lock
 * *
 * ******************************************/
GW_shared_lock::GW_shared_lock(GW_shared_mutex& mtx): m_mtx(mtx)
{
	m_mtx.rdlock();
}

GW_shared_lock::~GW_shared_lock()
{
	m_mtx.unlock();
}


/*********************************************
 * *
 * *GW_unique_lock
 * *
 * ******************************************/
GW_unique_lock::GW_unique_lock(GW_shared_mutex& mtx): m_mtx(mtx)
{
	m_mtx.wrlock();
}

GW_unique_lock::~GW_unique_lock()
{
	m_mtx.unlock();
}

