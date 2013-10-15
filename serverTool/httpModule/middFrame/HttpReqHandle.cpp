#include "HttpReqHandle.h"

HttpReqHandle::HttpReqHandle()
{
	m_epfd = -1;
}

HttpReqHandle::~HttpReqHandle()
{
}


void* HttpReqHandle::threadProc(void* param)
{
	HttpReqHandle*  pWork = (HttpReqHandle*)(param);
	if (pWork)
	{
		pWork->threadWork();
	}

	return NULL;
}

void HttpReqHandle::threadWork(void)
{
	//init epoll variable
	m_epfd = epoll_create(EPOLLHINT);
	if (m_epfd < 0)
	{
		fprintf(stderr, "httpReqHandle call epoll_create failed!!!\n");
		exit(0);
	}
	int nfds = 0;
	struct epoll_event events[1024];

	// limit task number in epoll listening descriptor
	m_reqInNetInterface = 0;
	// if g_req_list do not have task, thread will wait 500 ms
	bool  taskExit = true;
	while( 1 )
	{
		while (m_reqInNetInterface < THETASKOFNUMBER )
		{
			HttpReqMsg*  pMsg = g_req_list.getAndPopFront();
			if (!pMsg)
			{
				taskExit = false;
				break;
			}

			HttpConnect  conn;
			if (conn.connect2HttpServ(pMsg->m_url) < 0)
			{
				pMsg->m_ret = RES_FAILED;
				g_res_list.push(pMsg);
				continue;
			}

			if (pMsg->m_type == REQ_GET)
			{
				if (HttpDataDispatcher::handleGetRequest(conn) < 0)
				{
					pMsg->m_ret = RES_FAILED;
					g_res_list.push(pMsg);
					continue;
				}
			}
			else if (pMsg->m_type == REQ_POST)
			{
				if (HttpDataDispatcher::handlePostRequest(conn, pMsg) < 0)
				{
					pMsg->m_ret = RES_FAILED;
					g_res_list.push(pMsg);
					continue;
				}
			}
			else
			{
				pMsg->m_ret = RES_FAILED;
				g_res_list.push(pMsg);
				conn.Close();
				continue;
			}

			// add socket to epoll interface
			struct  epoll_event ev;
			ev.data.fd = conn.m_socket;
			ev.events = EPOLLIN | EPOLLET;
			if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, conn.m_socket, &ev) < 0)
			{
				pMsg->m_ret = RES_FAILED;
				g_res_list.push(pMsg);
				conn.Close();
				continue;
			}

			Metadata4HttpReq  meta;
			meta.tStart = time(0);
			meta.fd = conn.m_socket;
			meta.pReq = pMsg;
			m_wait_list.insert(std::make_pair(conn.m_socket, meta));

			++m_reqInNetInterface;
		}

		// handle coming message
		nfds = epoll_wait(m_epfd, events, EPOLLHINT, 20);
		eventHandler(events, nfds);

		if (!taskExit)
		{
			usleep(20000);
		}
	}
}

void HttpReqHandle::eventHandler(struct epoll_event* nEvents, int nfds)
{
	for (int i = 0; i < nfds; ++i)
	{
		if (nEvents[i].data.fd == -1)
		{
			--m_reqInNetInterface;
			continue;
		}

		if (nEvents[i].events & EPOLLIN)
		{
			std::map<int, Metadata4HttpReq>::iterator it = m_wait_list.find(nEvents[i].data.fd);
			if (it != m_wait_list.end())
			{
				if (nEvents[i].data.fd != it->second.fd)
				{
					epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
					it->second.pReq->m_ret = RES_FAILED;
					g_res_list.push(it->second.pReq);
					m_wait_list.erase(it);

					close(nEvents[i].data.fd);
					--m_reqInNetInterface;
					continue;
				}

				if (!((it->second.pReq)->m_data) || 0 == ((it->second.pReq)->m_length)) // recv http header
				{
					int ret = HttpUtil::Recv(nEvents[i].data.fd, it->second.rBuf, 4096);
					if (ret < 0)
					{
						epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
						it->second.pReq->m_ret = RES_FAILED;
						g_res_list.push(it->second.pReq);
						m_wait_list.erase(it);

						close(nEvents[i].data.fd);
						--m_reqInNetInterface;
						continue;
					}
					else if (ret == 0)
					{
						continue;
					}
					else
					{
					}
				}
				else // recv http body
				{
					int ret = HttpUtil::Recv(nEvents[i].data.fd, (it->second.pReq)->m_data, (it->second.pReq)->m_length);
					if (ret < 0)
					{
						epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
						it->second.pReq->m_ret = RES_FAILED;
						g_res_list.push(it->second.pReq);
						m_wait_list.erase(it);

						close(nEvents[i].data.fd);
						--m_reqInNetInterface;
						continue;
					}
					else if (ret == 0)
					{
						continue;
					}
					else
					{
					}
				}
			}
			else
			{
				epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
				close(nEvents[i].data.fd);
				--m_reqInNetInterface;
			}
		}
	}
}

