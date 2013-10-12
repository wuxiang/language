#ifndef  _HTTPUTIL_H_
#define  _HTTPUTIL_H_

namespace HttpUtil
{

int setnonblocking(int sock)
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

long long mstime(void)
{
    struct timeval tv;
    long long mst;

    gettimeofday(&tv, NULL);
    mst = ((long)tv.tv_sec)*1000;
    mst += tv.tv_usec/1000;
    return mst;
}

}

#endif //_HTTPUTIL_H_
