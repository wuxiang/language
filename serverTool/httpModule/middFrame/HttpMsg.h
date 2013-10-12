#ifndef HTTP_MESSAGE_H_
#define HTTP_MESSAGE_H_
#include <string.h>

class  HttpReqMsg
{
public:
	uint32_t   m_timeout;
	char       m_url[1024];
	uint8_t    m_type;
	char       m_param[1024];
	uint8_t    m_ret;
	uint32_t   m_length;
	char*      m_data;

	HttpReqMsg(): m_timeout(0), m_type(0), m_ret(0), m_length(0), m_data(NULL)
	{
		bzero(m_url, 1024);
		bzero(m_param, 1024);
	}

	HttpReqMsg(const HttpReqMsg& req)
	{
		m_timeout = req.m_timeout;

		bzero(m_url, 1024);
		memcpy(m_url, req.m_url);

		m_type = req.m_type;

		bzero(m_param, 1024);
		memcpy(m_param, req.m_param);

		m_ret = req.m_ret;

		if (req.m_data)
		{
			m_length = strlen(req.m_data);
			m_data = new char[m_length + 1];
			memcpy(m_data, req.m_data);
		}
		else
		{
			m_length = 0;
		}
	}

	HttpReqMsg&  operator=(const HttpReqMsg& req)
	{
		m_timeout = req.m_timeout;

		bzero(m_url, 1024);
		memcpy(m_url, req.m_url);

		m_type = req.m_type;

		bzero(m_param, 1024);
		memcpy(m_param, req.m_param);

		m_ret = req.m_ret;

		if (req.m_data)
		{
			m_length = strlen(req.m_data);
			m_data = new char[m_length + 1];
			memcpy(m_data, req.m_data);
		}
		else
		{
			m_length = 0;
			m_data = NULL;
		}
	}

	~HttpReqMsg()
	{
		delete []m_data;
	}
};

#endif  //HTTP_MESSAGE_H_
