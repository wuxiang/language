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

//int HttpConnect::Send(unsigned char *Buf,int len)
//{
//    int pos=0,ret = 0;
//    if ( (NULL == Buf) || (len<=0) || (m_socket < 0) )
//    return -1;
//
//    while ( ret = send(m_socket,&Buf[pos],len,0))
//    {
//        //printf("SendDataToLink =%d, send len=%d,nSize=%d\n",m_socket, ret,len );
//        if (ret == len)
//        return ret;
//
//        if (  ret == 0  )
//        {
//            close(m_socket);
//            m_socket = -1;
//        }
//        else if ( ret < 0   )
//        {
//            if ( errno == EAGAIN || errno == EINTR )
//            {
//                usleep( 10000 );
//                continue;
//            }
//            else
//            {
//                close(m_socket);
//                m_socket = -1;
//                break;
//            }
//        }
//        else if ( ret<len )
//        {
//            pos += ret;
//            len -= ret;
//        }
//    }
//
//    if (  ret == 0  )
//    {
//        close(m_socket);
//        m_socket = -1;
//    }
//
//    return pos;
//}

//int HttpConnect::Recv(unsigned char *Buf,int len,int ms)
//{
//    int pos=0,length =0;
//    long long PreMs=mstime();
//
//    while( (mstime()-PreMs < ms) && ( pos < len ) )
//    {
//        usleep(50000);
//        length = recv(m_socket , &Buf[pos] , len - pos , 0 );
//        //printf("recv length=%d, pos=%d\n",length,pos);
//        if (length == 0)
//        {
//            close(m_socket);
//            m_socket=-1;
//            return pos;
//        }
//        else if (length < 0)
//        {
//            if ( errno == EAGAIN  ||  errno == EINTR  )
//            {
//                //usleep(500000);
//                continue;
//            }
//            else
//            {
//                close(m_socket);
//                m_socket=-1;
//                return pos;
//            }
//        }
//        else
//        {
//            pos += length;
//            //usleep(500000);
//        }
//    }
//
//    return pos;
//}
//
//int HttpConnect::Post(char *url,unsigned char *Buf,int len)
//{
//	if ( Connect(m_nIP,m_nPort) <0 )
//		return -1;
//    char PostHead[1024]={"POST %s HTTP/1.0\r\nAccept: */*\r\nhost: %s\r\nPragma: no-cache\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s"};
//
//    char Sendbuf[5120]={0};
//    sprintf(Sendbuf,PostHead,url,m_sDomain,len,Buf);
//
//    return Send((unsigned char *)Sendbuf,strlen(Sendbuf));
//}
//
//int HttpConnect::Get(unsigned char *Buf,int len)
//{
//	if ( Connect(m_nIP,m_nPort) <0 )
//		return -1;
//    char GetHead[1024]={"GET %s HTTP/1.1\r\nAccept: image/gif, */*\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)Host: %s\r\nConnection: Keep-Alive\r\n\r\n"};
//
//    char Sendbuf[2048]={0};
//    sprintf(Sendbuf,GetHead,Buf,m_sDomain);
//
//    return Send((unsigned char *)Sendbuf,strlen(Sendbuf));
//}
//

//int HttpConnect::GetURL(char *URL)
//{
//	SetURL(URL);
//	if ( Connect(m_nIP,m_nPort) <0 )
//		return -1;
//    char GetHead[1024]={"GET %s HTTP/1.1\r\nAccept: image/gif, */*\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\r\nHost: %s\r\nConnection: Close\r\n\r\n"};
//
//    char Sendbuf[2048]={0};
//    sprintf(Sendbuf,GetHead,m_sPath,m_sDomain);
//
//    return Send((unsigned char *)Sendbuf,strlen(Sendbuf));
//}
//
//int HttpConnect::PostData(unsigned char *Buf,int len)
//{
//    if ( Connect(m_nIP,m_nPort) <0 )
//    return -1;
//
//    char PostHead[1024]={"POST %s HTTP/1.0\r\nAccept: */*\r\nhost: %s\r\nPragma: no-cache\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s"};
//
//    char Sendbuf[5120]={0};
//    sprintf(Sendbuf,PostHead,m_sPath,m_sDomain,len,Buf);
//
//    return Send((unsigned char *)Sendbuf,strlen(Sendbuf));
//}

//int HttpConnect::RecvData(char *Buf,int len)
//{
//    int rt=Recv((unsigned char *)Buf,len);
//	//printf("### rt=%d,recrbuf=:\n%s\n",rt,Buf);
//	int datalen=0;
//    if ( rt>0 )
//    {
//		char *pStr= strstr(Buf,"\r\n\r\n") + strlen("\r\n\r\n");
//
//		if(strstr(Buf,"Content-Length: "))
//		{
//			datalen=atoi(strstr(Buf,"Content-Length: ")+strlen("Content-Length: "));
//		}
//		else if(strstr(Buf,"Transfer-Encoding: chunked"))
//		{
//			datalen=Hex2Int(strstr(Buf,"\r\n\r\n")+strlen("\r\n\r\n"));
//			pStr=strstr(pStr,"\r\n") + strlen("\r\n");
//		}
//		else
//		{
//			datalen=strlen(pStr) ;
//		}
//
//		memmove(Buf,pStr,datalen);
//		Buf[datalen]='\0';
//    }
//    return datalen;
//}

