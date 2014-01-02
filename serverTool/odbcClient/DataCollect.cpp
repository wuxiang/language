#include "DataCollect.h"

CDataCollect::CDataCollect()
{

}


CDataCollect::~CDataCollect()
{
}

bool CDataCollect::ReadDataFromDB( char *szSqlString,unsigned int& iLength)
{
	if (!m_ODBCHand.IsOpen())
	{
		if (!m_ODBCHand.Open())
		{
			return false;
		}
		if (!m_ODBCHand.Connect("sqlwineinfo2","ec","ec123"))
		{
			return false;
		}
	}
	memset(m_pDBDataMemory,0,sizeof(m_pDBDataMemory));
	m_ODBCHand.Clear();
	m_ODBCHand.SQLQuery(szSqlString);
	ResHead* pResHead = (ResHead *)m_pDBDataMemory;
	pResHead->rows = m_ODBCHand.GetCount();
	pResHead->columns = m_ODBCHand.GetColumns();
	iLength = sizeof(ResHead);
	char *pszStrCol = NULL; //某行某例的数据
	int szColLen = 0;       //某行某例的数据长度
	int nOffset = 0;        //描述字符串长度所占字节
	char *pPressStr = NULL;
	for (int iRow = 0;iRow<pResHead->rows;iRow++)
	{
		for (int i=0;i<pResHead->columns;i++)
		{
			pszStrCol = m_ODBCHand.GetStrValue(i);
			if(pszStrCol[0])
			{
				szColLen = strlen(pszStrCol);
				pPressStr = CResDataParser::ProcessSYN(szColLen,nOffset);
				memcpy(m_pDBDataMemory+iLength,pPressStr,nOffset);
				iLength += nOffset;
				memcpy(m_pDBDataMemory+iLength,pszStrCol,szColLen);
				iLength += szColLen;
			}
			else
			{
				m_pDBDataMemory[iLength++] = 0;
			}
		}	
		if (!m_ODBCHand.Next())
		{
			if (iRow<pResHead->rows-1)
			{
				return false;
			}
			break;
		}
	}
	pResHead->ilength = iLength-sizeof(ResHead);
	return true;
}

unsigned int CDataCollect::StrToUl( const string& data )
{
	if (0 == data.length())
	{
		return 0;
	}
	return strtoul(data.c_str(), NULL, 10);
}

bool CDataCollect::StrNCpy( char *buf, const int StartPos, const int MaxSize, const string & data )
{
	if (NULL == buf || StartPos < 0 || StartPos >= MaxSize)
	{
		return false;
	}
	if (0 == data.length())
	{
		memset(buf + StartPos, 0, MaxSize - StartPos);
	}
	strncpy(buf + StartPos, data.c_str(), MaxSize - StartPos);
	return true;
}

bool CDataCollect::StrToTime( const string& data,DateTime& date )
{
	if (data.size()<12)
	{
		sscanf(data.c_str(),"%u/%u/%u",&date.m_wYear,&date.m_nMonth,&date.m_nDay);
		date.m_nHour = 0;
		date.m_nMin = 0;
		date.m_nSeconds = 0;
	}
	else
	{
		sscanf(data.c_str(),"%u/%u/%u %u:%u:%u",&date.m_wYear,&date.m_nMonth,&date.m_nDay,&date.m_nHour,&date.m_nMin,&date.m_nSeconds);
	}
	return true;
}

double CDataCollect::StrToDouble( const string& data )
{
	if (0 == data.length())
	{
		return 0;
	}
	return strtod(data.c_str(), NULL);
}

int CDataCollect::StrToInt( const string& data )
{
	if (0 == data.length())
	{
		return 0;
	}
	return atoi(data.c_str());
}

CDataCollect* CDataCollect::GetInstance()
{
	static CDataCollect s_dataCollecter;
	return &s_dataCollecter;
}
