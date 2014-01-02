#ifndef HTTPREQHANDLE_H_
#define HTTPREQHANDLE_H_
#include <sys/epoll.h>

#include <map>

#include "HttpGlobal.h"
#include "HttpConnect.h"
#include "HttpDataDispatcher.h"

class HttpReqHandle
{
public:
	HttpReqHandle();
	~HttpReqHandle();

	static void* threadProc(void* param);

	void threadWork(void);

private:
	void eventHandler(struct epoll_event* events, int nfds);
	void checkTimeout();

private:
	int  m_epfd;
	size_t  m_reqInNetInterface;
	std::map<int, Metadata4HttpReq>  m_wait_list;
};

#endif //HTTPREQHANDLE_H_
