#ifndef _GLOBFUNC_H_
#define _GLOBFUNC_H_
#include "Common.h"
#include "md5.h"

#ifdef  __cplusplus
extern "C" {
#endif

void Bin2Str(char *c, void *ptr, int sz);
void Str2Bin(char *c, void *ptr, int sz);
int PassCMP(char *pass_md5_str, char *passwd);

#ifdef  __cplusplus
}
#endif

#endif
