#ifndef _MONGOWRAP_H_
#define _MONGOWRAP_H_
#define  MONGO_HAVE_STDINT
#include <mongo.h>
#include <bson.h>
#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include "metadata.h"
#include "config.h"
#include "urlEncode.h"

enum mongo_status
{
	MONGO_CONNECT_INIT,
	MONGO_CONNECT_ERROR,
	MONGO_CONNECT_OK,
};

struct  UserRelation
{
	std::string   uname;
	std::string   macIP;
	std::string   mobile;
	std::string   pushID;
	uint8_t       platform;
};

class MongoWrap
{
public:
	MongoWrap();
	~MongoWrap();
	void setMongoInfo(const std::map<std::string, unsigned int>& ServInfo, char*  user, char* pass);
	bool mongoConnect();
	bool mongoUpdate(const char* const db, bson* query, bson* field, int flag = MONGO_UPDATE_UPSERT | MONGO_UPDATE_MULTI);
	bool getCursor(const char* const db, bson* query, bson* field, mongo_cursor* cursor);
	bool querylimitRecord(const char* const db,	int limit, mongo_cursor* cursor);
	bool mongoInsert(const char* const db, bson* object);
	bool mongoRemove(const char* const db, bson* object);

	bool updateAccInfo(AllInfor4Upload& info, bool needUpdateName = true);
	bool getPhoneNumByMacIP(const std::string& macIP, std::string& phone);
	bool getCurrBindPhone(const std::string& macIP, std::string& phone);
	bool setPhoneNumByMacIP(const std::string& macIP, const std::string& phone);

	// check user's passwd
	bool checkUserPasswd(const std::string& name, const std::string& passwd);

	// update client id in AccUserCache
	//bool updateExternalInfoInAccUserCache(AllInfor4Upload& info);

	// separate db handle function
	bool  queryAllStockDataWithName(const std::string& uname, const char* db, std::vector<AtomRecordDB>& vRes);
	bool  queryGroupDataInCloud(AtomRecordDB& cond);
	bool  queryGroupDataInCloud(AtomRecordDB& cond, std::set<_SymbolStock>& sset);
	bool  queryGroupDataInStock(AtomRecordDB& cond);
	bool  queryGroupDataInStock(AtomRecordDB& cond, std::set<_SymbolStock>& sset);

	bool  setStkOfRecInDB(AtomRecordDB& atomData);
	bool  addStk2RecInDB(AtomRecordDB& atomData);
	bool  delStkRecInDB(AtomRecordDB& atomData);

	bool  queryAllStockDataWithMacIP(const std::string& macIP, std::vector<AtomRecordDB>& vRes);
	bool  queryGroupDataInDevDB(AtomRecordDB& cond);
	bool  queryGroupDataInDevDB(AtomRecordDB& cond, std::set<_SymbolStock>& sset);

	bool  setStkOfRecInDevDB(AtomRecordDB& atomData);
	bool  addStk2RecInDevDB(AtomRecordDB& atomData);
	bool  delStkRecInDevDB(AtomRecordDB& atomData);

	bool  getUserAccount(const std::string& macIP, std::string& name);
	bool  getUserInfo(const std::string& macIP, UserRelation&  uInfo);
	bool  removeMacIPData(const std::string& macIP);
	bool  resetUserMacIP(const std::string& name, const std::string& macIP);
	bool  unsetUserName(const std::string& macIP);

private:
	std::map<std::string, unsigned int> m_mgoServerInfo;
	char        m_user[255];
	char        m_pass[255];

	int         m_status;
	mongo       m_mongo;
};

#endif //_MONGOWRAP_H_
