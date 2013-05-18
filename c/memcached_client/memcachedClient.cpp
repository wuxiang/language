#include "memcachedClient.h"

MemcachedClient::MemcachedClient()
{
	m_fd = -1;
	m_status = 0;
	m_lastAlive = 0;
	bzero(m_name, 64);
	m_port = 0;

	RBuf.Reserve(2048);
	SBuf.Reserve(2048);
}

MemcachedClient::~MemcachedClient()
{
	if (m_fd != -1)
	{
		disconnect();
	}
}


bool MemcachedClient::connect2Cached(const char* ip, int port)
{
	bzero(m_name, 64);
	strncpy(m_name, ip, 64);
	m_port = port;

	if (-1 == (m_fd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		return false;
	}

	//+++++++++++++++++++set flag for descript++++++++++++++++++
	int flag = fcntl(m_fd, F_GETFL);
	fcntl(m_fd, F_SETFL, flag|O_NONBLOCK);

	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	setsockopt( m_fd, SOL_SOCKET, SO_SNDTIMEO, ( char * )&tv, sizeof( tv ) );
	setsockopt( m_fd, SOL_SOCKET, SO_RCVTIMEO, ( char * )&tv, sizeof( tv ) );
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(m_name);
	addr.sin_port = htons(m_port);

	int	retval = connect(m_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

	if (retval == 0)
	{
		m_status = 2 ;
	}
	else if (retval == -1 )
	{
		if(errno == EINPROGRESS || errno == EALREADY )
		{
			m_status = 1 ;
		}

		if(errno == EISCONN )
		{
			m_status = 2 ;
		}
	}
	g_log.Wlog(1,"memcached CONN retval=%d, fd=%d ,pBind->nStatus=%d\n",retval, m_fd, m_status);

	if (m_status != 1 && m_status != 2)
	{
		return false;
	}

	return true;
}

bool MemcachedClient::disconnect()
{
	close(m_fd);
	m_fd = -1;
	m_status = 0;

	return true;
}

int	 MemcachedClient::getFd()
{
	return m_fd;
}

void MemcachedClient::resetfd()
{
	m_fd = -1;
}

char MemcachedClient::getstatus()
{
	return m_status;
}

void MemcachedClient::setstatus(char st)
{
	m_status = st;
}

off_t MemcachedClient::raw_command(const uint8_t cmd,
									const void* key, const size_t keylen,
									const void* dta, const size_t dtalen,
									const uint32_t opaque, CDBuffer& buf)
{
    /* all of the storage commands use the same command layout */
	if (!key)
	{
		return 0;
	}

	if (!dta && dtalen != 0)
	{
		return 0;
	}

    protocol_binary_request_no_extras request;
    memset(&request, 0, sizeof(protocol_binary_request_no_extras));

    request.message.header.request.magic = PROTOCOL_BINARY_REQ;
    request.message.header.request.opcode = cmd;
    request.message.header.request.keylen = htons(keylen);
    request.message.header.request.bodylen = htonl(keylen + dtalen);
    request.message.header.request.opaque = opaque;

    off_t key_offset = sizeof(protocol_binary_request_no_extras);
	buf.append(&request, key_offset);

    if (key != NULL) {
		buf.append(key, keylen);
    }
    if (dta != NULL) {
		buf.append(dta, dtalen);
    }

    return key_offset + keylen + dtalen;
}

bool  MemcachedClient::cmdGetStock(const char* uname)
{
	g_log.Wlog(5, "%s: %d_get_%s\n", __FUNCTION__, __LINE__, uname);
	if (!uname)
	{
		return false;
	}
	uint32_t hashID = hash(uname, strlen(uname), SEED);

    size_t len = raw_command(PROTOCOL_BINARY_CMD_GET, uname, strlen(uname), NULL, 0, hashID, SBuf);
	if (0 == len)
	{
		return false;
	}

	std::map<uint32_t, std::list<std::string> >::iterator iter = m_reqTable.find(hashID);
	if (iter != m_reqTable.end())
	{
		iter->second.push_back(uname);
	}
	else
	{
		m_reqTable.insert(std::make_pair(hashID, std::list<std::string>(1, std::string(uname))));
	}
	return true;
}

off_t MemcachedClient::storage_command(const uint8_t cmd,
										const void* key, const size_t keylen,
										const void* dta, const size_t dtalen,
										uint32_t flags, uint32_t exp, const uint32_t opaque,
										CDBuffer& buf)
{
	if (!key || !dta)
	{
		return 0;
	}

    protocol_binary_request_set request;
    memset(&request, 0, sizeof(protocol_binary_request_set));

    request.message.header.request.magic = PROTOCOL_BINARY_REQ;
    request.message.header.request.opcode = cmd;
    request.message.header.request.keylen = htons(keylen);
    request.message.header.request.extlen = 8;
    request.message.header.request.bodylen = htonl(keylen + 8 + dtalen);
    request.message.header.request.opaque = opaque;
    request.message.body.flags = flags;
    request.message.body.expiration = exp;

    off_t key_offset = sizeof(protocol_binary_request_no_extras) + 8;
	buf.append(&request, key_offset);

	buf.append(key, keylen);
	buf.append(dta, dtalen);

    return key_offset + keylen + dtalen;
}

bool  MemcachedClient::cmdSetStock(const char* uname, CDBuffer& buf)
{
	g_log.Wlog(5, "%s: %d_get_%s\n", __FUNCTION__, __LINE__, uname);
	if (!uname || 0 == buf.Size())
	{
		return false;
	}

	uint32_t hashID = hash(uname, strlen(uname), SEED);

    if (0 == storage_command(PROTOCOL_BINARY_CMD_SET, uname, strlen(uname), buf.Data(), buf.Size(), 0, 0, hashID, SBuf))
	{
		return false;
	}
	return true;
}

bool  MemcachedClient::getResult(std::string& name, std::string& value, protocol_binary_response_status& status)
{
	bool flag  = false;
	do {
		size_t  offset = sizeof(protocol_binary_response_no_extras);
		if (RBuf.Size() < offset)
		{
			return false;
		}
		protocol_binary_response_no_extras* response = (protocol_binary_response_no_extras *)RBuf.Data();
		uint16_t keylen = ntohs(response->message.header.response.keylen);
		uint16_t st = ntohs(response->message.header.response.status);
		uint32_t bodylen = ntohl(response->message.header.response.bodylen);

		if (RBuf.Size() < offset + bodylen)
		{
			return false;
		}

		if (PROTOCOL_BINARY_CMD_SET == response->message.header.response.opcode)
		{
			RBuf.CutHead(offset + bodylen);
			continue;
		}

		std::map<uint32_t, std::list<std::string> >::iterator iter = m_reqTable.find(response->message.header.response.opaque);
		if (iter != m_reqTable.end())
		{
			if (0 == iter->second.size())
			{
				flag = false;
				m_reqTable.erase(iter);
			}
			else if (1 == iter->second.size())
			{
				name = *(iter->second.begin());
				m_reqTable.erase(iter);
				flag = true;
			}
			else
			{
				name = (iter->second.front());
				iter->second.pop_front();
				flag = true;
			}
		}

		if (flag)
		{
			char* ptr = (char*)(response + 1);
			value.assign(ptr + keylen + response->message.header.response.extlen,
					bodylen - keylen - response->message.header.response.extlen);
			status = (protocol_binary_response_status)st;
		}

		RBuf.CutHead(offset + bodylen);
	}
	while (1);


	return flag;
}

time_t MemcachedClient::getActiveTime()
{
	return m_lastAlive;
}

void  MemcachedClient::setActiveTime(time_t tm)
{
	m_lastAlive = tm;
}
