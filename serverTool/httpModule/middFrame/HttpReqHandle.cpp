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

		checkTimeout();

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
					(it->second.pReq)->m_ret = RES_FAILED;
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
						(it->second.pReq)->m_ret = RES_FAILED;
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
						int dataLen = 0;
						char* pData = NULL;

						char* pPosLen = strstr(it->second.rBuf,"Content-Length: ");
						if (pPosLen)
						{
							dataLen = atoi(pPosLen + strlen("Content-Length: "));
							pData = strstr(it->second.rBuf, "\r\n\r\n") + strlen("\r\n\r\n");
						}
						else
						{
							char* pPosEncode = strstr(it->second.rBuf, "Transfer-Encoding: chunked");
							if (pPosEncode)
							{
								char* pCRLF = strstr(it->second.rBuf, "\r\n\r\n");
								dataLen = HttpUtil::Hex2Int(pCRLF + strlen("\r\n\r\n"));
								pData = strstr((pCRLF + strlen("\r\n\r\n")), "\r\n") + strlen("\r\n");
							}
						}

						if (!pData || 0 == dataLen)
						{
							continue;
						}


						if (strlen(pData) > dataLen)
						{
							epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
							(it->second.pReq)->m_ret = RES_FAILED;
							g_res_list.push(it->second.pReq);
							m_wait_list.erase(it);

							close(nEvents[i].data.fd);
							--m_reqInNetInterface;
							continue;
						}

						(it->second.pReq)->m_length = dataLen;
						(it->second.pReq)->m_data = new char[dataLen + 1];
						memcpy((it->second.pReq)->m_data, pData, strlen(pData));
						if (dataLen == strlen(pData))
						{
							epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
							(it->second.pReq)->m_ret = RES_OK;
							g_res_list.push(it->second.pReq);
							m_wait_list.erase(it);

							close(nEvents[i].data.fd);
							--m_reqInNetInterface;
						}
					}
				}
				else // recv http body
				{
					int ret = HttpUtil::Recv(nEvents[i].data.fd, (it->second.pReq)->m_data, (it->second.pReq)->m_length);
					if (ret < 0)
					{
						epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
						(it->second.pReq)->m_ret = RES_FAILED;
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
						if ((it->second.pReq)->m_length == strlen((it->second.pReq)->m_data))
						{
							epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
							(it->second.pReq)->m_ret = RES_OK;
							g_res_list.push(it->second.pReq);
							m_wait_list.erase(it);

							close(nEvents[i].data.fd);
							--m_reqInNetInterface;
						}
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
		else
		{
			epoll_ctl(m_epfd, EPOLL_CTL_DEL, nEvents[i].data.fd, NULL);
			close(nEvents[i].data.fd);
			--m_reqInNetInterface;
		}
	}
}

void HttpReqHandle::checkTimeout()
{
	std::map<int, Metadata4HttpReq>::iterator it = m_wait_list.begin();
	while (it != m_wait_list.end())
	{
		if ((time(0) - it->second.tStart) > (it->second.pReq)->m_timeout)
		{
			epoll_ctl(m_epfd, EPOLL_CTL_DEL, it->second.fd, NULL);
			(it->second.pReq)->m_ret = RES_FAILED;
			g_res_list.push(it->second.pReq);
			m_wait_list.erase(it++);
			continue;
		}

		++it;
	}
}

