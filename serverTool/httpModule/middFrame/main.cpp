#include <stdio.h>
#include <pthread.h>

#include "HttpGlobal.h"
#include "HttpMsg.h"
#include "HttpReqHandle.h"

int main()
{
	//HttpReqMsg* pMsg = new HttpReqMsg();
	//pMsg->m_timeout = 20;
	//strcpy(pMsg->m_url, "http://www.baidu.com/img/bdlogo.gif");
	//strcpy(pMsg->m_url, "http://www.sina.com.cn/index.html");
	//strcpy(pMsg->m_url, "http://www.baidu.com/");
	for (int i = 1; i <= 1; ++i)
	{
		HttpReqMsg* pMsg = new HttpReqMsg();
		pMsg->m_timeout = 20;
		sprintf(pMsg->m_url, "http://news.baidu.com/n?cmd=4&class=civilnews&pn=%d&sub=0", i);
		//strcpy(pMsg->m_url, "http://www.sina.com.cn/index.html");
		//strcpy(pMsg->m_url, "http://www.baidu.com/");
		fprintf(stderr, "%s\n", pMsg->m_url);
		pMsg->m_type = REQ_GET;
		g_req_list.push(pMsg);
	}

	HttpReqHandle* pHandle = new HttpReqHandle();
	pthread_t id;
	if (pthread_create(&id, NULL, HttpReqHandle::threadProc, (void*)pHandle))
	{
		fprintf(stderr, "create thread failed\n");
		exit(0);
	}

	sleep(30);

	int idxSucc = 0;
	int idxFailed = 0;
	int tryTime = 0;
	while (true)
	{
		HttpReqMsg* ptr = g_res_list.getAndPopFront();
		if (ptr)
		{
			if (ptr->m_ret == RES_OK)
			{
				++idxSucc;
				//fprintf(stdout, "\n%s\n", ptr->m_data);
				fprintf(stderr, "\nhandle message success\n");
			}
			else
			{
				++idxFailed;
				fprintf(stderr, "\nhandle message failed\n");
			}
		}
		else
		{
			++tryTime;
			if (tryTime == 3)
			{
				break;
			}
			usleep(1000000);
		}
	}

	fprintf(stderr, "\ntotal task: 20, success: %d, failed: %d\n", idxSucc, idxFailed);
	fprintf(stderr, "\nmain thread exiting\n");
	return 0;
}
