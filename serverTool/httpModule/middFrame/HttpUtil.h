#ifndef  _HTTPUTIL_H_
#define  _HTTPUTIL_H_

namespace HttpUtil
{

inline int setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        //perror("fcntl(sock,GETFL)");
        return -1;
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        //perror("fcntl(sock,SETFL,opts)");
        return -1;
    }
    return 0;
}

inline long long mstime(void)
{
    struct timeval tv;
    long long mst;

    gettimeofday(&tv, NULL);
    mst = ((long)tv.tv_sec)*1000;
    mst += tv.tv_usec/1000;
    return mst;
}

inline int Hex2Int(const char* str)
{
    int nResult = 0;
    while (*str != '\0')
    {
        switch (*str)
        {
        case '0'...'9':
            nResult = nResult*16 + *str-'0';
            break;
        case 'a'...'f':
            nResult = nResult*16 + *str-'a'+10;
            break;
        case 'A'...'F':
            nResult = nResult*16 + *str-'A'+10;
            break;
        default:
            return -1;
            break;
        }
        str++;
    }
    return nResult;
}

inline int HttpSend(int& socket, char *Buf,int len)
{
    int pos = 0;
	int ret = 0;
    if ( (NULL == Buf) || (len <= 0) || (socket < 0) )
	{
		return -1;
	}

    while ( (ret = send(socket, &Buf[pos], len, 0)))
    {
        if (ret == len)
		{
			return ret;
		}

        if (  ret == 0  )
        {
            close(socket);
            socket = -1;
        }
        else if ( ret < 0   )
        {
            if ( errno == EAGAIN || errno == EINTR )
            {
                usleep( 10000 );
                continue;
            }
            else
            {
                close(socket);
                socket = -1;
                break;
            }
        }
        else if ( ret < len )
        {
            pos += ret;
            len -= ret;
        }
    }

    if (  ret <= 0  )
    {
        close(socket);
        socket = -1;
    }

    return pos;
}

inline int Recv(int& socket, char *Buf, int len)
{
	int pos = strlen(Buf);
	int length = recv(socket , &Buf[pos] , len - pos , 0 );

	if (length == 0)
	{
		close(socket);
		socket=-1;

		return -1;
	}
	else if (length < 0)
	{
		if ( errno == EAGAIN  ||  errno == EINTR  )
		{
			return 0;
		}
		else
		{
			close(socket);
			socket=-1;

			return -1;
		}
	}
	else
	{
		pos += length;
	}

	return pos;
}

}
#endif //_HTTPUTIL_H_
