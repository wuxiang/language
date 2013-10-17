#include <stdio.h>
#include <pthread.h>

#include "HttpGlobal.h"
#include "HttpMsg.h"
#include "HttpReqHandle.h"

int main()
{
	HttpReqMsg* pMsg = new HttpReqMsg();
	pMsg->m_timeout = 20;
	strcpy(pMsg->m_url, "http://www.baidu.com/img/bdlogo.gif");
	//strcpy(pMsg->m_url, "http://www.sina.com.cn/index.html");
	//strcpy(pMsg->m_url, "http://www.baidu.com/");
	pMsg->m_type = REQ_GET;
	g_req_list.push(pMsg);

	HttpReqHandle* pHandle = new HttpReqHandle();
	pthread_t id;
	if (pthread_create(&id, NULL, HttpReqHandle::threadProc, (void*)pHandle))
	{
		fprintf(stderr, "create thread failed\n");
		exit(0);
	}

	sleep(20);

	HttpReqMsg* ptr = g_res_list.getAndPopFront();
	if (ptr)
	{
		if (ptr->m_ret == RES_OK)
		{
			fprintf(stdout, "\n%s\n", ptr->m_data);
		}
		else
		{
			fprintf(stderr, "\nhandle message failed\n");
		}
	}
	else
	{
		fprintf(stderr, "get NULL ptr");
	}

	fprintf(stderr, "\nmain thread exiting\n");
	return 0;
}
