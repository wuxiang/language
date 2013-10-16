#include "HttpConnect.h"

HttpConnect::HttpConnect(void)
{
    m_socket = -1;
    m_sDomain[0] = '\0';
    m_sPath[0] = '\0';
    m_nIP = 0;
    m_nPort = 0;
}

HttpConnect::~HttpConnect(void)
{
}

long HttpConnect::Domain2IP(char *sDomain)
{
    struct hostent *host=gethostbyname(sDomain);
    in_addr   in;
    memmove(&in, host->h_addr_list[0], sizeof(in_addr));
    return in.s_addr;
}

int HttpConnect::connect2HttpServ(char *URL)
{
	if (SetURL(URL) < 0)
	{
		return -1;
	}

    if ( Connect(m_nIP,m_nPort) < 0 )
	{
		return -1;
	}

	return m_socket;
}

int HttpConnect::Connect(char *sIP,int port)
{
    return Connect(inet_addr(sIP),port);
}

int HttpConnect::Connect(long  nIP,int port)
{
    if ( m_socket >= 0)
    {
        close(m_socket);
        m_socket =-1;
    }
    m_socket = socket(AF_INET,SOCK_STREAM,0);
    if ( m_socket < 0)
    return -1;

    struct sockaddr_in servaddr;
    socklen_t socklen = sizeof(servaddr);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = nIP;
    servaddr.sin_port = htons(port);

    struct timeval tv;
    tv.tv_sec =15;
    tv.tv_usec = 0;
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));

    if (connect(m_socket,(struct sockaddr*)&servaddr, socklen) < 0)
    {
		close(m_socket);
        return -1;
    }
    HttpUtil::setnonblocking(m_socket);

    return 0;
}

int HttpConnect::Status()
{
    return m_socket;
}

int HttpConnect::Close()
{
    close(m_socket);
    m_socket=-1;
    return 0;
}

int HttpConnect::SetURL(char *URL)
{
    memset(&m_sDomain,0,sizeof(m_sDomain));
    memset(&m_sPath,0,sizeof(m_sPath));
    m_nIP = 0;
    m_nPort = 80;

    char *p1,*p2;

    p1 = strcasestr(URL,"http://") + 7;
    if(!p1)
	{
		return -1;
	}

    p2 = strcasestr(p1,":");
    if(p2)
    {
        m_nPort=atoi(p2+1);
        strncpy(m_sDomain,p1,p2-p1);
        p2=strcasestr(p1,"/");
    }
    else
    {
        p2=strcasestr(p1,"/");
        if(p2)
        strncpy(m_sDomain,p1,p2-p1);
    }


    if(!p2)
    return -1;

    strcpy(m_sPath,p2);
    m_nIP = Domain2IP(m_sDomain);

    return 0;
}

