#ifndef HTTP_DATA_DISPATCHER_H_
#define HTTP_DATA_DISPATCHER_H_
#include "HttpConnect.h"
#include "HttpUtil.h"
#include "HttpMsg.h"

class HttpDataDispatcher
{
public:
	static int handleGetRequest(HttpConnect& conn);
	static int handlePostRequest(HttpConnect& conn, HttpReqMsg* pMsg);
};

#endif //HTTP_DATA_DISPATCHER_H_
