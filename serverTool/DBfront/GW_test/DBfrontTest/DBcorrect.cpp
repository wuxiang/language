#include "DBcorrect.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

DBcorrectTest::DBcorrectTest()
{
	strcpy(m_conf.host, "10.15.107.61");
	strcpy(m_conf.user, "wuxiang");
	strcpy(m_conf.pass, "wuxiang@DB");
	strcpy(m_conf.dbName, "TestDB");

	m_conf.port = 3306;

}

void DBcorrectTest::runCreateDB()
{
	//char*   pSentence = "CREATE DATABASE IF NOT EXISTS 'TestDB' DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci";
	//char*   pGrant = "GRANT ALL PRIVILEGES ON TestDB.* TO 'wuxiang'@'%' IDENTIFIED BY 'wuxiang@DB'";
	char*     pCreatTable = "CREATE TABLE IF NOT EXISTS  student (studentID INT UNIQUE PRIMARY KEY, score INT, name CHAR(100) NOT NULL)";

	GW_DBfront      front("testDB", m_conf);
	front.start();
	front.put(pCreatTable);

	sleep(10);

	sqlInfo     info;
	front.status(info);
	printf("commit number: %d\ndone number: %d\nerror number: %d\n", info.commit_num, info.done_num, info.err_num);
}


