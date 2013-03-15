#ifndef _GWMUTEX_H_
#define _GWMUTEX_H_
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

class GW_mutex_base
{
public:
	GW_mutex_base()
	{
	}

	virtual ~GW_mutex_base()
	{
	}

	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual bool try_lock() = 0;

private:
	GW_mutex_base(const GW_mutex_base&);
	GW_mutex_base& operator=(const GW_mutex_base&);
};

class GW_mutex: public GW_mutex_base
{
public:
	GW_mutex();
	~GW_mutex();
	void lock();
	void unlock();
	bool try_lock();

private:
	pthread_mutex_t   m_mutex;
};

class GW_spin_lock: public GW_mutex_base
{
public:
	GW_spin_lock();
	~GW_spin_lock();
	void lock();
	void unlock();
	bool try_lock();

private:
	pthread_spinlock_t   m_mutex;
};

class GW_shared_mutex
{
public:
	GW_shared_mutex();
	~GW_shared_mutex();
	void rdlock();
	void wrlock();
	bool try_rdlock();
	bool try_wrlock();
	void unlock();
private:
	pthread_rwlock_t     m_mutex;
};

class GW_lock_guard
{
public:
	explicit GW_lock_guard(GW_mutex& mtx);
	explicit GW_lock_guard(GW_spin_lock& mtx);
	~GW_lock_guard();

private:
	explicit GW_lock_guard(const GW_lock_guard&);
	GW_lock_guard operator=(const GW_lock_guard&);

private:
	GW_mutex_base&   m_mutex;
};

class GW_shared_lock
{
public:
	explicit  GW_shared_lock(GW_shared_mutex& mtx);
	~GW_shared_lock();

private:
	explicit GW_shared_lock(const GW_shared_lock &);
	GW_shared_lock operator=(const GW_shared_lock &);

private:
	GW_shared_mutex&    m_mtx;
};

class GW_unique_lock
{
public:
	explicit  GW_unique_lock(GW_shared_mutex& mtx);
	~GW_unique_lock();

private:
	explicit GW_unique_lock(const GW_unique_lock&);
	GW_unique_lock operator=(const GW_unique_lock&);

private:
	GW_shared_mutex&    m_mtx;
};

#endif //_GWMUTEX_H_
