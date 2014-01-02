
#ifndef	_CPP_ODBC_H_
#define	_CPP_ODBC_H_

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#include <string>
using namespace std;

//查询的最大字段数量
#define FIELD_NUM 1024
#define FIELD_MAX_LEN 36

class CppODBC
{
public:
	CppODBC( );
	virtual ~CppODBC( );
//公共接口
public:
	bool		Open( );
	bool		Close( );
	//第三步连接数据库
	bool 		Connect( const char* pszDSN, const char* pszUName, const char* pszUPasswd );
	bool 		DisConnect( );
	bool 		Clear( );
	int			SetFieldMaxLen( int nMaxLen );
	unsigned int 	SQLQuery( const char* pszSQL );
	unsigned int	SQLExec( const char* pszSQL );
	bool 	SQLExecAutoID( const char *pszSQL, const char* pIdField, long &lIdentity );
	bool	IsOpen( );
	//查询的结果数量，更新时返回更新的记录数量，删除时返回删除的数量
	unsigned int  	GetCount( );
	//返回查询结果的列数
	unsigned int  	GetColumns( );
	int  			GetIntValue( unsigned int uiIndex );
	double 			GetDoubleValue( unsigned int uiIndex );
	char *   		GetStrValue( unsigned int uiIndex );
	//取消操作
   bool     		Cancel( );
	//获取错误代码
	unsigned int  	GetError( );
	//下一个
	bool     		Next( );
	bool			Eof( );
	
	void 			Lock();
	void 			UnLock();

private:
	SQLHENV			 	V_OD_Env_;				// Handle ODBC environment 存放环境变量
	SQLHDBC			 	V_OD_hdbc_;				// Handle connection 连接句柄
	SQLHSTMT 		 	V_OD_hstmt_;			// SQL语句的句柄
	SQLINTEGER		 	V_OD_rowanz_;			// 操作影响的记录数量
	SQLSMALLINT			V_OD_colanz_;			// 操作影响的记录包含的字段数量
	char*				pszField_[FIELD_NUM];	// 存放一条查询结果集,缓冲区根据查询结果创建
	int				    nMaxFiledLen_;				//字段的最大值
	bool 				bOpened_;
	bool				bConnected_;
	bool 				bEof_;
	int				errorNO;		//错误码
};

#endif


