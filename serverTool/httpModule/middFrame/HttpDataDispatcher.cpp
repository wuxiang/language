#include "HttpDataDispatcher.h"

int HttpDataDispatcher::handleGetRequest(HttpConnect& conn)
{
	if (conn.m_socket < 0)
	{
		return -1;
	}

    char GetHead[1024] = {"GET %s HTTP/1.1\r\nAccept: image/gif, */*\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\r\nHost: %s\r\nConnection: Close\r\n\r\n"};

    char Sendbuf[2048] = { 0 };
    sprintf(Sendbuf, GetHead, conn.m_sPath, conn.m_sDomain);

	if (HttpUtil::HttpSend(conn.m_socket, Sendbuf, strlen(Sendbuf)) < 0)
	{
		if (conn.m_socket >= 0)
		{
			conn.Close();
		}
		return -1;
	}

	return 0;
}

int HttpDataDispatcher::handlePostRequest(HttpConnect& conn, HttpReqMsg* pMsg)
{
	if (conn.m_socket < 0)
	{
		return -1;
	}

	if (!pMsg)
	{
		conn.Close();
		return -1;
	}

    char PostHead[1024] = {"POST %s HTTP/1.0\r\nAccept: */*\r\nhost: %s\r\nPragma: no-cache\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s"};

    char Sendbuf[5120] = { 0 };
    sprintf(Sendbuf,PostHead, conn.m_sPath, conn.m_sDomain, strlen(pMsg->m_param), pMsg->m_param);

	if (HttpUtil::HttpSend(conn.m_socket, Sendbuf, strlen(Sendbuf)) < 0)
	{
		if (conn.m_socket >= 0)
		{
			conn.Close();
		}
		return -1;
	}

	return 0;
}

