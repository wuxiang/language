#ifndef HTTP_CONST_H_
#define HTTP_CONST_H_
#include "GWFifo.h"

const size_t THETASKOFNUMBER = 5;
const size_t EPOLLHINT = 1024;

typedef enum {
	REQ_GET = 0x6,
	REQ_POST,
} RequestType;

typedef enum {
	RES_FAILED = 0x4,
	RES_OK,
}ResultType;

extern  GWFifo    g_req_list;
extern  GWFifo    g_res_list;
extern int  tTime;

#endif //HTTP_CONST_H_
