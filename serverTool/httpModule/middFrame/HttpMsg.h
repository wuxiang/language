#ifndef HTTP_MESSAGE_H_
#define HTTP_MESSAGE_H_
#include <string.h>

class  HttpReqMsg
{
public:
	uint32_t   m_timeout;
	char       m_url[2048];
	uint8_t    m_type;
	char       m_param[4096];
	uint8_t    m_ret;
	int        m_length;
	char*      m_data;

	HttpReqMsg(): m_timeout(0), m_type(0), m_ret(0), m_length(0), m_data(NULL)
	{
		bzero(m_url, 1024);
		bzero(m_param, 4096);
	}

	HttpReqMsg(const HttpReqMsg& req)
	{
		m_timeout = req.m_timeout;

		bzero(m_url, 1024);
		memcpy(m_url, req.m_url, strlen(m_url));

		m_type = req.m_type;

		bzero(m_param, 4096);
		memcpy(m_param, req.m_param, strlen(m_param));

		m_ret = req.m_ret;

		if (req.m_data && m_length)
		{
			m_length = req.m_length;
			m_data = new char[m_length + 1];
			memcpy(m_data, req.m_data, m_length);
		}
		else
		{
			m_length = 0;
			m_data = NULL;
		}
	}

	HttpReqMsg&  operator=(const HttpReqMsg& req)
	{
		m_timeout = req.m_timeout;

		bzero(m_url, 1024);
		memcpy(m_url, req.m_url, strlen(m_url));

		m_type = req.m_type;

		bzero(m_param, 4096);
		memcpy(m_param, req.m_param, strlen(m_param));

		m_ret = req.m_ret;

		if (req.m_data && m_length)
		{
			m_length = req.m_length;
			m_data = new char[m_length + 1];
			memcpy(m_data, req.m_data, m_length);
		}
		else
		{
			m_length = 0;
			m_data = NULL;
		}

		return *this;
	}

	~HttpReqMsg()
	{
		delete []m_data;
	}
};

class  Metadata4HttpReq
{
public:
	char   rBuf[4096];
	uint32_t   tStart;
	int  fd;
	int  bufPos;
	HttpReqMsg*  pReq;

	Metadata4HttpReq(): tStart(0), fd(-1), bufPos(0), pReq(NULL)
	{
		bzero(rBuf, 4096);
	}

	Metadata4HttpReq(const Metadata4HttpReq& req)
	{
		bzero(rBuf, 4096);
		memcpy(rBuf, req.rBuf, 4096);
		tStart = req.tStart;
		fd = req.fd;
		bufPos = req.bufPos;
		pReq = req.pReq;
	}

	Metadata4HttpReq& operator=(const Metadata4HttpReq& req)
	{
		bzero(rBuf, 4096);
		memcpy(rBuf, req.rBuf, 4096);
		tStart = req.tStart;
		fd = req.fd;
		bufPos = req.bufPos;
		pReq = req.pReq;

		return *this;
	}

	~Metadata4HttpReq()
	{
	}
};

#endif  //HTTP_MESSAGE_H_
