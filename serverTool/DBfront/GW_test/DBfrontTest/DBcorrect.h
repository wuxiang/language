#ifndef _DBCORRECT_H_
#define _DBCORRECT_H_
#include "stForMysql.h"
#include "GWDBfront.h"

class DBcorrectTest
{
public:
	DBcorrectTest();
	void runCreateDB();

private:
	db_config   m_conf;
};

#endif //
