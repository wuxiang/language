#ifndef HTTPREQHANDLE_H_
#define HTTPREQHANDLE_H_

class HttpReqHandle
{
public:
	HttpReqHandle();
	~HttpReqHandle();

	static void* start(void* param);
private:
	size_t   m_task_idx;
};

#endif //HTTPREQHANDLE_H_
