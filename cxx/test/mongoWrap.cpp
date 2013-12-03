#include "mongoWrap.h"
#include "g_function.h"

MongoWrap::MongoWrap(): m_status(MONGO_CONNECT_INIT)
{
	m_mgoServerInfo.clear();
	bzero(m_user, 255);
	bzero(m_pass, 255);
	mongo_init(&m_mongo);
}

MongoWrap::~MongoWrap()
{
	mongo_disconnect(&m_mongo);
	mongo_destroy(&m_mongo);
}

void MongoWrap::setMongoInfo(const std::map<std::string, unsigned int>& ServInfo, char*  user, char* pass)
{
	m_mgoServerInfo = ServInfo;

	if (user)
	{
		strncpy(m_user, user, (strlen(user) > 255 ? 255 : strlen(user)));
	}

	if (pass)
	{
		strncpy(m_pass, pass, (strlen(pass) > 255 ? 255 : strlen(pass)));
	}
}

bool MongoWrap::mongoConnect()
{
	int status = MONGO_ERROR;
	std::map<std::string, unsigned int>::iterator it = m_mgoServerInfo.begin();
	while (it != m_mgoServerInfo.end())
	{
		status = mongo_connect(&m_mongo, it->first.c_str(), it->second);
		if (MONGO_OK == status)
		{
			break;
		}
		else
		{
			g_log.Wlog(0, "failed mongos: IP(%s), Port(%d)!!!\n", it->first.c_str(), it->second);
		}
		++it;
	}

	if (MONGO_OK != status)
	{
		g_log.Wlog(0, "connect to mongodb failed: %d\n", m_mongo.err);
		m_status = MONGO_CONNECT_ERROR;
		return false;
	}

	return true;
}

bool MongoWrap::mongoUpdate(const char* const db, bson* query, bson* field, int flag)
{
	if (MONGO_OK != mongo_update(&m_mongo, db, query, field, flag, NULL))
	{
		if (mongoConnect())
		{
			if (MONGO_OK != mongo_update(&m_mongo, db, query, field, flag, NULL))
			{
				g_log.Wlog(0, "write data to mongodb failed: %s !!!\n", m_mongo.errstr);
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	return true;
}

bool MongoWrap::mongoInsert(const char* const db, bson* object)
{
	if (MONGO_OK != mongo_insert(&m_mongo, db, object, NULL))
	{
		if (mongoConnect())
		{
			if (MONGO_OK != mongo_insert(&m_mongo, db, object, NULL))
			{
				g_log.Wlog(0, "write data to mongodb failed: %s !!!\n", m_mongo.errstr);
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	return true;
}

bool MongoWrap::mongoRemove(const char* const db, bson* object)
{
	if (MONGO_OK != mongo_remove(&m_mongo, db, object, NULL))
	{
		if (mongoConnect())
		{
			if (MONGO_OK != mongo_remove(&m_mongo, db, object, NULL))
			{
				g_log.Wlog(0, "write data to mongodb failed: %s !!!\n", m_mongo.errstr);
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	return true;
}

bool MongoWrap::getCursor(const char* const db, bson* query, bson* field, mongo_cursor* cursor)
{
	mongo_cursor_init(cursor, &m_mongo, db);
	mongo_cursor_set_query(cursor, query);
	if (field)
	{
		mongo_cursor_set_fields(cursor, field);
	}

	return true;
}

bool MongoWrap::querylimitRecord(const char* const db, int limit, mongo_cursor* cursor)
{
	if (!cursor)
	{
		return false;
	}

	mongo_cursor_init(cursor, &m_mongo, db);
	mongo_cursor_set_limit(cursor, limit);
	return true;
}

bool MongoWrap::updateAccInfo(AllInfor4Upload& info, bool needUpdateName)
{
	if (HttpUtility::hasChineseCharacter(info.name) && !HttpUtility::isUtf8String(info.name, strlen(info.name)))
	{
		return false;
	}

	if (needUpdateName && strlen(info.name) || info.pushID.first.length() || info.phoneNum.length() || info.clientID.length())
	{
		bson query;
		bson_init(&query);
		{
			bson_append_string(&query, "macIP", info.macIP.c_str());
		}
		bson_finish(&query);

		bson field;
		bson_init(&field);
		{
			bson_append_start_object(&field, "$set");
			{
				if (strlen(info.name))
				{
					bson_append_string(&field, "name", info.name);
				}

				if (info.pushID.first.length())
				{
					bson_append_string(&field, "pushID", info.pushID.first.c_str());
					bson_append_int(&field, "platform", info.pushID.second);
				}

				if (info.phoneNum.length())
				{
					bson_append_string(&field, "phoneNum", info.phoneNum.c_str());
				}

				if (info.clientID.length())
				{
					bson_append_string(&field, "clientID", info.clientID.c_str());
				}
			}
			bson_append_finish_object(&field);
		}
		bson_finish(&field);

		bool flag = mongoUpdate(Config::instance().getRelationDB(), &query, &field);

		bson_destroy(&query);
		bson_destroy(&field);

		return flag;
	}

	return true;
}

bool MongoWrap::queryAllStockDataWithName(const std::string& uname, const char* db, std::vector<AtomRecordDB>& vRes)
{
	bson query;
	bson_init(&query);
	{
		if (!strcmp(db, Config::instance(). getStockDataDB()))
		{
			bson_append_string(&query, "UName", uname.c_str());
		}
		else if (!strcmp(db,Config::instance().getSyncronizeDB()))
		{
			bson_append_string(&query, "userid",uname.c_str());
		}
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		if (!strcmp(db, Config::instance(). getStockDataDB()))
		{
			bson_append_int(&field, "sort", 1);
			bson_append_int(&field, "group", 1);
		}
		bson_append_int(&field, "content", 1);
		bson_append_int(&field, "time", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(db, &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t   tm = 0;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		AtomRecordDB  tmpRec;
		tmpRec.uname = uname;

		bson_iterator it[1];

		if (!strcmp(db, Config::instance(). getStockDataDB()))
		{
			if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "sort"))
			{
				tmpRec.sort = (uint8_t)bson_iterator_int(it);
			}

			if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "group"))
			{
				tmpRec.group = (uint8_t)bson_iterator_int(it);
			}
		}
		else
		{
			tmpRec.sort = 1;
			tmpRec.group = 1;
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			tmpRec.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			if (!strcmp(db, Config::instance(). getStockDataDB()))
			{
				bson_iterator subIter[1];
				bson_iterator_subiterator(it, subIter);

				// scanner array object
				while (BSON_EOO != bson_iterator_next(subIter))
				{
					bson obj[1];
					bson_iterator_subobject(subIter, obj);

					bson_iterator  objIte[1];
					if (BSON_EOO != bson_find(objIte, obj, "data"))
					{
						stk = bson_iterator_string(objIte);

						tm = 0;
						if (BSON_EOO != bson_find(objIte, obj, "time"))
						{
							tm = bson_iterator_long(objIte);
						}

						tmpRec.content.push_back(_SymbolStock(stk, tm));
					}
				}
			}
			else if (!strcmp(db, Config::instance().getSyncronizeDB()))
			{
				bson  subobj[1];
				bson_iterator_subobject(it, subobj);

				bson_iterator  subIter[1];
				if (BSON_EOO != bson_find(subIter, subobj, "group0"))
				{
					bson_iterator  subsubIter[1];
					bson_iterator_subiterator(subIter, subsubIter);
					while (BSON_EOO != bson_iterator_next(subsubIter))
					{
						bson  desObj[1];
						bson_iterator_subobject(subsubIter, desObj);

						bson_iterator  stkIte[1];
						if (BSON_EOO != bson_find(stkIte, desObj, "data"))
						{
							stk = bson_iterator_string(stkIte);
							tm = 0;
							if (BSON_EOO != bson_find(stkIte, desObj, "time"))
							{
								tm = bson_iterator_long(stkIte);
							}

							tmpRec.content.push_back(_SymbolStock(stk, tm));
						}
					}
				}
			}
		}

		vRes.push_back(tmpRec);
		flag = true;

		if (!strcmp(db, Config::instance().getSyncronizeDB()))
		{
			break;
		}
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::getUserInfo(const std::string& macIP, UserRelation&  uInfo)
{
	if (0 == macIP.length())
	{
		return false;
	}

	uInfo.macIP = macIP;

	bson  query;

	bson_init(&query);
	bson_append_string(&query, "macIP", macIP.c_str());
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "name", 1);
		bson_append_int(&field, "pushID", 1);
		bson_append_int(&field, "platform", 1);
		bson_append_int(&field, "phoneNum", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getRelationDB(), &query, &field, &cursor);

	bool flag = false;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "name"))
		{
			uInfo.uname = bson_iterator_string(it);
			flag = true;
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "pushID"))
		{
			uInfo.pushID = bson_iterator_string(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "platform"))
		{
			uInfo.platform = bson_iterator_int(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "phoneNum"))
		{
			uInfo.mobile = bson_iterator_string(it);
		}
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::getUserAccount(const std::string& macIP, std::string& name)
{
	if (0 == macIP.length())
	{
		return false;
	}
	bson  query;

	bson_init(&query);
	bson_append_string(&query, "macIP", macIP.c_str());
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "name", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getRelationDB(), &query, &field, &cursor);

	bool flag = false;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "name"))
		{
			name = bson_iterator_string(it);
			flag = true;
		}
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool MongoWrap::resetUserMacIP(const std::string& name, const std::string& macIP)
{
	if (HttpUtility::hasChineseCharacter(name) && !HttpUtility::isUtf8String(name.c_str(), name.length()))
	{
		return false;
	}

	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", macIP.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$set");
		{
			bson_append_string(&field, "name", name.c_str());
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = mongoUpdate(Config::instance().getRelationDB(), &query, &field);

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool MongoWrap::unsetUserName(const std::string& macIP)
{
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", macIP.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$unset");
		{
			bson_append_string(&field, "name", "");
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = mongoUpdate(Config::instance().getRelationDB(), &query, &field);

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool MongoWrap::setPhoneNumByMacIP(const std::string& macIP, const std::string& phone)
{
	if (!macIP.length() || !phone.length())
	{
		return false;
	}

	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", macIP.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$set");
		{
			bson_append_string(&field, "phoneNum", phone.c_str());
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = mongoUpdate(Config::instance().getRelationDB(), &query, &field);

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool MongoWrap::getCurrBindPhone(const std::string& macIP, std::string& phone)
{
	bson  query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", macIP.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "phoneNum", 1);
		bson_append_int(&field, "name", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getRelationDB(), &query, &field, &cursor);

	bool flag = false;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator  it[1];
		if (BSON_EOO == bson_find(it, mongo_cursor_bson(&cursor), "name"))
		{
			if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "phoneNum"))
			{
				phone = bson_iterator_string(it);
				flag = true;
				break;
			}
		}
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool MongoWrap::getPhoneNumByMacIP(const std::string& macIP, std::string& phone)
{
	bson  query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", macIP.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "phoneNum", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getRelationDB(), &query, &field, &cursor);

	bool flag = false;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator  it[1];
		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "phoneNum"))
		{
			phone = bson_iterator_string(it);
			flag = true;
			break;
		}
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool MongoWrap::checkUserPasswd(const std::string& name, const std::string& passwd)
{
	bson  query;
	bson_init(&query);
	{
		bson_append_string(&query, "UName", name.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "PWord", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getUserCacheDB(), &query, &field, &cursor);

	bool flag = false;
	std::string md5passwd;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator  it[1];
		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "PWord"))
		{
			md5passwd.assign(bson_iterator_string(it));
			flag = true;
		}
		break;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	if (flag)
	{
		char  md5[256] = { 0 };
		char  common[256] = { 0 };
		strncpy(md5, md5passwd.c_str(), 256);
		strncpy(common, passwd.c_str(), 256);

		if(!PassCMP(md5, common))
		{
			return true;
		}

		return false;
	}

	return false;
}

bool  MongoWrap::queryGroupDataInCloud(AtomRecordDB& cond)
{
	if (!cond.uname.length())
	{
		return false;
	}

	bson  query;
	bson_init(&query);
	{
		bson_append_string(&query, "userid", cond.uname.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "time", 1);
		bson_append_int(&field, "content", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getSyncronizeDB(), &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t tm = 0;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			cond.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			bson  subobj[1];
			bson_iterator_subobject(it, subobj);

			bson_iterator  subIter[1];
			if (BSON_EOO != bson_find(subIter, subobj, "group0"))
			{
				bson_iterator  subsubIter[1];
				bson_iterator_subiterator(subIter, subsubIter);
				while (BSON_EOO != bson_iterator_next(subsubIter))
				{
					bson  desObj[1];
					bson_iterator_subobject(subsubIter, desObj);

					bson_iterator  stkIte[1];
					if (BSON_EOO != bson_find(stkIte, desObj, "data"))
					{
						stk = bson_iterator_string(stkIte);
						tm = 0;
						if (BSON_EOO != bson_find(stkIte, desObj, "time"))
						{
							tm = bson_iterator_long(stkIte);
						}
						cond.content.push_back(_SymbolStock(stk, tm));
					}
				}
			}
		}

		flag = true;
		break;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::queryGroupDataInStock(AtomRecordDB& cond)
{
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "UName", cond.uname.c_str());
		bson_append_int(&query, "sort", cond.sort);
		bson_append_int(&query, "group", cond.group);
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "time", 1);
		bson_append_int(&field, "content", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getStockDataDB(), &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t   tm = 0;;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			cond.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			bson_iterator subIter[1];
			bson_iterator_subiterator(it, subIter);

			// scanner array object
			while (BSON_EOO != bson_iterator_next(subIter))
			{
				bson obj[1];
				bson_iterator_subobject(subIter, obj);

				bson_iterator  objIte[1];
				if (BSON_EOO != bson_find(objIte, obj, "data"))
				{
					stk = bson_iterator_string(objIte);

					tm = 0;
					if (BSON_EOO != bson_find(objIte, obj, "time"))
					{
						tm = bson_iterator_long(objIte);
					}

					cond.content.push_back(_SymbolStock(stk, tm));
				}
			}
		}

		flag = true;
		break;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::queryGroupDataInCloud(AtomRecordDB& cond, std::set<_SymbolStock>& sset)
{
	if (!cond.uname.length())
	{
		return false;
	}

	bson  query;
	bson_init(&query);
	{
		bson_append_string(&query, "userid", cond.uname.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "time", 1);
		bson_append_int(&field, "content", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getSyncronizeDB(), &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t tm = 0;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			cond.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			bson  subobj[1];
			bson_iterator_subobject(it, subobj);

			bson_iterator  subIter[1];
			if (BSON_EOO != bson_find(subIter, subobj, "group0"))
			{
				bson_iterator  subsubIter[1];
				bson_iterator_subiterator(subIter, subsubIter);
				while (BSON_EOO != bson_iterator_next(subsubIter))
				{
					bson  desObj[1];
					bson_iterator_subobject(subsubIter, desObj);

					bson_iterator  stkIte[1];
					if (BSON_EOO != bson_find(stkIte, desObj, "data"))
					{
						stk = bson_iterator_string(stkIte);
						tm = 0;
						if (BSON_EOO != bson_find(stkIte, desObj, "time"))
						{
							tm = bson_iterator_long(stkIte);
						}
						sset.insert(_SymbolStock(stk, tm));
					}
				}
			}
		}

		flag = true;
		break;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::queryGroupDataInStock(AtomRecordDB& cond, std::set<_SymbolStock>& sset)
{
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "UName", cond.uname.c_str());
		bson_append_int(&query, "sort", cond.sort);
		bson_append_int(&query, "group", cond.group);
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "time", 1);
		bson_append_int(&field, "content", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getStockDataDB(), &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t   tm = 0;;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			cond.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			bson_iterator subIter[1];
			bson_iterator_subiterator(it, subIter);

			// scanner array object
			while (BSON_EOO != bson_iterator_next(subIter))
			{
				bson obj[1];
				bson_iterator_subobject(subIter, obj);

				bson_iterator  objIte[1];
				if (BSON_EOO != bson_find(objIte, obj, "data"))
				{
					stk = bson_iterator_string(objIte);

					tm = 0;
					if (BSON_EOO != bson_find(objIte, obj, "time"))
					{
						tm = bson_iterator_long(objIte);
					}

					sset.insert(_SymbolStock(stk, tm));
				}
			}
		}

		flag = true;
		break;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::setStkOfRecInDB(AtomRecordDB& atomData)
{
	if (HttpUtility::hasChineseCharacter(atomData.uname) && !HttpUtility::isUtf8String(atomData.uname.c_str(), atomData.uname.length()))
	{
		return false;
	}

	bson query;
	bson_init(&query);
	{
		if (1 == atomData.sort && 1 == atomData.group)
		{
			bson_append_string(&query, "userid", atomData.uname.c_str());
		}
		else
		{
			bson_append_string(&query, "UName", atomData.uname.c_str());
			bson_append_int(&query, "sort", atomData.sort);
			bson_append_int(&query, "group", atomData.group);
		}
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$set");
		{
			std::string  des;
			if (1 == atomData.sort && 1 == atomData.group)
			{
				des.assign("content.group0");
			}
			else
			{
				des.assign("content");
			}

			bson_append_start_array(&field, des.c_str());
			{
				int i = 0;
				char  buf[64];
				std::vector<_SymbolStock>::const_iterator iter = atomData.content.begin();
				while (iter != atomData.content.end())
				{
					bzero(buf, 64);
					sprintf(buf, "%d", i);

					bson_append_start_object(&field, buf);
					{
						bson_append_string(&field, "data", iter->stk.c_str());
						bson_append_long(&field, "time", iter->tm);
					}
					bson_append_finish_object(&field);

					++i;
					++iter;
				}
			}
			bson_append_finish_array(&field);

			bson_append_long(&field, "time", atomData.ver);

			if (1 == atomData.sort && 1 == atomData.group)
			{
				bson_append_string(&field, "fileName", "mystock0.json");
			}

		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = false;
	if (1 == atomData.sort && 1 == atomData.group)
	{
		flag = mongoUpdate(Config::instance().getSyncronizeDB(), &query, &field);
	}
	else
	{
		flag = mongoUpdate(Config::instance().getStockDataDB(), &query, &field);
	}

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool  MongoWrap::addStk2RecInDB(AtomRecordDB& atomData)
{
	if (HttpUtility::hasChineseCharacter(atomData.uname) && !HttpUtility::isUtf8String(atomData.uname.c_str(), atomData.uname.length()))
	{
		return false;
	}

	bson query;
	bson_init(&query);
	{
		if (1 == atomData.sort && 1 == atomData.group)
		{
			bson_append_string(&query, "userid", atomData.uname.c_str());
		}
		else
		{
			bson_append_string(&query, "UName", atomData.uname.c_str());
			bson_append_int(&query, "sort", atomData.sort);
			bson_append_int(&query, "group", atomData.group);
		}
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$pushAll");
		{
			std::string  des;
			if (1 == atomData.sort && 1 == atomData.group)
			{
				des.assign("content.group0");
			}
			else
			{
				des.assign("content");
			}

			bson_append_start_array(&field, des.c_str());
			{
				int i = 0;
				char  buf[64];
				std::vector<_SymbolStock>::const_iterator iter = atomData.content.begin();
				while (iter != atomData.content.end())
				{
					bzero(buf, 64);
					sprintf(buf, "%d", i);

					bson_append_start_object(&field, buf);
					{
						bson_append_string(&field, "data", iter->stk.c_str());
						bson_append_long(&field, "time", iter->tm);
					}
					bson_append_finish_object(&field);

					++i;
					++iter;
				}
			}
			bson_append_finish_array(&field);
		}
		bson_append_finish_object(&field);

		bson_append_start_object(&field, "$set");
		{
			bson_append_long(&field, "time", atomData.ver);

			if (1 == atomData.sort && 1 == atomData.group)
			{
				bson_append_string(&field, "fileName", "mystock0.json");
			}
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = false;
	if (1 == atomData.sort && 1 == atomData.group)
	{
		flag = mongoUpdate(Config::instance().getSyncronizeDB(), &query, &field);
	}
	else
	{
		flag = mongoUpdate(Config::instance().getStockDataDB(), &query, &field);
	}

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool  MongoWrap::delStkRecInDB(AtomRecordDB& atomData)
{
	if (HttpUtility::hasChineseCharacter(atomData.uname) && !HttpUtility::isUtf8String(atomData.uname.c_str(), atomData.uname.length()))
	{
		return false;
	}

	bson query;
	bson_init(&query);
	{
		if (1 == atomData.sort && 1 == atomData.group)
		{
			bson_append_string(&query, "userid", atomData.uname.c_str());
		}
		else
		{
			bson_append_string(&query, "UName", atomData.uname.c_str());
			bson_append_int(&query, "sort", atomData.sort);
			bson_append_int(&query, "group", atomData.group);
		}
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$pullAll");
		{
			std::string  des;
			if (1 == atomData.sort && 1 == atomData.group)
			{
				des.assign("content.group0");
			}
			else
			{
				des.assign("content");
			}

			bson_append_start_array(&field, des.c_str());
			{
				int i = 0;
				char  buf[64];
				std::vector<_SymbolStock>::const_iterator iter = atomData.content.begin();
				while (iter != atomData.content.end())
				{
					bzero(buf, 64);
					sprintf(buf, "%d", i);

					bson_append_start_object(&field, buf);
					{
						bson_append_string(&field, "data", iter->stk.c_str());
						bson_append_long(&field, "time", iter->tm);
					}
					bson_append_finish_object(&field);

					++i;
					++iter;
				}
			}
			bson_append_finish_array(&field);
		}
		bson_append_finish_object(&field);

		bson_append_start_object(&field, "$set");
		{
			bson_append_long(&field, "time", atomData.ver);

			if (1 == atomData.sort && 1 == atomData.group)
			{
				bson_append_string(&field, "fileName", "mystock0.json");
			}
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = false;
	if (1 == atomData.sort && 1 == atomData.group)
	{
		flag = mongoUpdate(Config::instance().getSyncronizeDB(), &query, &field);
	}
	else
	{
		flag = mongoUpdate(Config::instance().getStockDataDB(), &query, &field);
	}

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool  MongoWrap::queryAllStockDataWithMacIP(const std::string& macIP, std::vector<AtomRecordDB>& vRes)
{
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", macIP.c_str());
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "sort", 1);
		bson_append_int(&field, "group", 1);
		bson_append_int(&field, "content", 1);
		bson_append_int(&field, "time", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getDevStockDataDB(), &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t   tm = 0;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		AtomRecordDB  tmpRec;
		tmpRec.macIP = macIP;

		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "sort"))
		{
			tmpRec.sort = (uint8_t)bson_iterator_int(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "group"))
		{
			tmpRec.group = (uint8_t)bson_iterator_int(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			tmpRec.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			bson_iterator subIter[1];
			bson_iterator_subiterator(it, subIter);

			// scanner array object
			while (BSON_EOO != bson_iterator_next(subIter))
			{
				bson obj[1];
				bson_iterator_subobject(subIter, obj);

				bson_iterator  objIte[1];
				if (BSON_EOO != bson_find(objIte, obj, "data"))
				{
					stk = bson_iterator_string(objIte);

					tm = 0;
					if (BSON_EOO != bson_find(objIte, obj, "time"))
					{
						tm = bson_iterator_long(objIte);
					}

					tmpRec.content.push_back(_SymbolStock(stk, tm));
				}
			}
		}

		vRes.push_back(tmpRec);
		flag = true;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::queryGroupDataInDevDB(AtomRecordDB& cond)
{
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", cond.macIP.c_str());
		bson_append_int(&query, "sort", cond.sort);
		bson_append_int(&query, "group", cond.group);
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "time", 1);
		bson_append_int(&field, "content", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getDevStockDataDB(), &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t   tm = 0;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			cond.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			bson_iterator subIter[1];
			bson_iterator_subiterator(it, subIter);

			// scanner array object
			while (BSON_EOO != bson_iterator_next(subIter))
			{
				bson obj[1];
				bson_iterator_subobject(subIter, obj);

				bson_iterator  objIte[1];
				if (BSON_EOO != bson_find(objIte, obj, "data"))
				{
					stk = bson_iterator_string(objIte);

					tm = 0;
					if (BSON_EOO != bson_find(objIte, obj, "time"))
					{
						tm = bson_iterator_long(objIte);
					}

					cond.content.push_back(_SymbolStock(stk, tm));
				}
			}
		}

		flag = true;
		break;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::queryGroupDataInDevDB(AtomRecordDB& cond, std::set<_SymbolStock>& sset)
{
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", cond.macIP.c_str());
		bson_append_int(&query, "sort", cond.sort);
		bson_append_int(&query, "group", cond.group);
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_int(&field, "time", 1);
		bson_append_int(&field, "content", 1);
	}
	bson_finish(&field);

	mongo_cursor cursor;
	getCursor(Config::instance().getDevStockDataDB(), &query, &field, &cursor);

	bool flag = false;
	std::string stk;
	uint64_t   tm = 0;
	while (MONGO_OK == mongo_cursor_next(&cursor))
	{
		bson_iterator it[1];

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "time"))
		{
			cond.ver = bson_iterator_long(it);
		}

		if (BSON_EOO != bson_find(it, mongo_cursor_bson(&cursor), "content"))
		{
			bson_iterator subIter[1];
			bson_iterator_subiterator(it, subIter);

			// scanner array object
			while (BSON_EOO != bson_iterator_next(subIter))
			{
				bson obj[1];
				bson_iterator_subobject(subIter, obj);

				bson_iterator  objIte[1];
				if (BSON_EOO != bson_find(objIte, obj, "data"))
				{
					stk = bson_iterator_string(objIte);

					tm = 0;
					if (BSON_EOO != bson_find(objIte, obj, "time"))
					{
						tm = bson_iterator_long(objIte);
					}

					sset.insert(_SymbolStock(stk, tm));
				}
			}
		}

		flag = true;
		break;
	}

	mongo_cursor_destroy(&cursor);
	bson_destroy(&field);
	bson_destroy(&query);

	return flag;
}

bool  MongoWrap::setStkOfRecInDevDB(AtomRecordDB& atomData)
{
	if (!(!atomData.uname.length() && atomData.macIP.length()))
	{
		return false;
	}
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", atomData.macIP.c_str());
		bson_append_int(&query, "sort", atomData.sort);
		bson_append_int(&query, "group", atomData.group);
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$set");
		{
			bson_append_start_array(&field, "content");
			{
				int i = 0;
				char  buf[64];
				std::vector<_SymbolStock>::const_iterator iter = atomData.content.begin();
				while (iter != atomData.content.end())
				{
					bzero(buf, 64);
					sprintf(buf, "%d", i);

					bson_append_start_object(&field, buf);
					{
						bson_append_string(&field, "data", iter->stk.c_str());
						bson_append_long(&field, "time", iter->tm);
					}
					bson_append_finish_object(&field);

					++i;
					++iter;
				}
			}
			bson_append_finish_array(&field);

			bson_append_long(&field, "time", atomData.ver);
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = mongoUpdate(Config::instance().getDevStockDataDB(), &query, &field);

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool  MongoWrap::addStk2RecInDevDB(AtomRecordDB& atomData)
{
	if (!(!atomData.uname.length() && atomData.macIP.length()))
	{
		return false;
	}
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", atomData.macIP.c_str());
		bson_append_int(&query, "sort", atomData.sort);
		bson_append_int(&query, "group", atomData.group);
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$pushAll");
		{
			bson_append_start_array(&field, "content");
			{
				int i = 0;
				char  buf[64];
				std::vector<_SymbolStock>::const_iterator iter = atomData.content.begin();
				while (iter != atomData.content.end())
				{
					bzero(buf, 64);
					sprintf(buf, "%d", i);

					bson_append_start_object(&field, buf);
					{
						bson_append_string(&field, "data", iter->stk.c_str());
						bson_append_long(&field, "time", iter->tm);
					}
					bson_append_finish_object(&field);

					++i;
					++iter;
				}
			}
			bson_append_finish_array(&field);

		}
		bson_append_finish_object(&field);

		bson_append_start_object(&field, "$set");
		{
			bson_append_long(&field, "time", atomData.ver);
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = mongoUpdate(Config::instance().getDevStockDataDB(), &query, &field);

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool  MongoWrap::delStkRecInDevDB(AtomRecordDB& atomData)
{
	if (!(!atomData.uname.length() && atomData.macIP.length()))
	{
		return false;
	}
	bson query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", atomData.macIP.c_str());
		bson_append_int(&query, "sort", atomData.sort);
		bson_append_int(&query, "group", atomData.group);
	}
	bson_finish(&query);

	bson field;
	bson_init(&field);
	{
		bson_append_start_object(&field, "$pullAll");
		{
			bson_append_start_array(&field, "content");
			{
				int i = 0;
				char  buf[64];
				std::vector<_SymbolStock>::const_iterator iter = atomData.content.begin();
				while (iter != atomData.content.end())
				{
					bzero(buf, 64);
					sprintf(buf, "%d", i);

					bson_append_start_object(&field, buf);
					{
						bson_append_string(&field, "data", iter->stk.c_str());
						bson_append_long(&field, "time", iter->tm);
					}
					bson_append_finish_object(&field);

					++i;
					++iter;
				}
			}
			bson_append_finish_array(&field);
		}
		bson_append_finish_object(&field);

		bson_append_start_object(&field, "$set");
		{
			bson_append_long(&field, "time", atomData.ver);
		}
		bson_append_finish_object(&field);
	}
	bson_finish(&field);

	bool flag = mongoUpdate(Config::instance().getDevStockDataDB(), &query, &field);

	bson_destroy(&query);
	bson_destroy(&field);

	return flag;
}

bool  MongoWrap::removeMacIPData(const std::string& macIP)
{
	bson  query;
	bson_init(&query);
	{
		bson_append_string(&query, "macIP", macIP.c_str());
	}
	bson_finish(&query);

	bool flag = mongoRemove(Config::instance().getDevStockDataDB(), &query);
	bson_destroy(&query);

	return flag;
}
