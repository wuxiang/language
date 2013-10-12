#ifndef _ACCUSERREG_H_
#define _ACCUSERREG_H_

#include "Common.h"
#include "DataCacheDefine.h"


class AccUserReg
{
public:
	AccUserReg(void);
	~AccUserReg(void);

	static void * Startting(void *argv);
	int AddToList(AccUserRegStruct *pAUR);
};
#endif
