#include "AccUserReg.h"
#include "CWorkThread.h"
#include "TeaEncrypt.h"
#include "CHttp.h"

extern CLog _log;
AccUserRegList_t g_AccUserRegList;
pthread_mutex_t g_AccUserRegListlock;
extern std::map<unsigned int, ServerIdTokickUser > g_mServIpToThread;

extern int RegEnable;
extern char AccUserRegAddr[128];


AccUserReg::AccUserReg(void)
{
	pthread_mutex_init(&g_AccUserRegListlock,NULL);
}

AccUserReg::~AccUserReg(void)
{
	pthread_mutex_destroy(&g_AccUserRegListlock);
}

char *url_encode(char const *s, int len,unsigned char *OUTBUF, int *new_length)
{
//#define safe_emalloc(nmemb, size, offset)	malloc((nmemb) * (size) + (offset))
	static unsigned char hexchars[] = "0123456789ABCDEF";
	register unsigned char c;
	unsigned char *to, *start;
	unsigned char const *from, *end;

	from = (unsigned char *)s;
	end = (unsigned char *)s + len;
	start = to = OUTBUF;//(unsigned char *) safe_emalloc(3, len, 1);

	while (from < end) {
		c = *from++;

		if (c == ' ') {
			*to++ = '+';
#ifndef CHARSET_EBCDIC
		} else if ((c < '0' && c != '-' && c != '.') ||
			(c < 'A' && c > '9') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z')) {
				to[0] = '%';
				to[1] = hexchars[c >> 4];
				to[2] = hexchars[c & 15];
				to += 3;
#else /*CHARSET_EBCDIC*/
		} else if (!isalnum(c) && strchr("_-.", c) == NULL) {
			/* Allow only alphanumeric chars and '_', '-', '.'; escape the rest */
			to[0] = '%';
			to[1] = hexchars[os_toascii[c] >> 4];
			to[2] = hexchars[os_toascii[c] & 15];
			to += 3;
#endif /*CHARSET_EBCDIC*/
		} else {
			*to++ = c;
		}
	}
	*to = 0;
	if (new_length) {
		*new_length = to - start;
	}
	return (char *) start;
}

void * AccUserReg::Startting(void *argv)
{
	AccUserRegStruct _theAccUserReg;
	std::map<unsigned int, ServerIdTokickUser>::iterator ServIpToThreaditer;
	AccUserRegList_t::iterator iter;

	CBase64 B64;
	CHttp http;
	http.SetURL(AccUserRegAddr);

	char buf[1024]={0};
	unsigned char SendBuf[1024]={0};
	int new_length;
	char recrbuf[1024]={0};
	char OutBuf[2048]={0};
	char UName[40]={0};
	char PWord[40]={0};
	char UNameB64[60]={0};
	char PWordB64[60]={0};
	unsigned char UNameB64URL[90]={0};
	unsigned char PWordB64URL[90]={0};
	char Ret=2;

	while ( 1 )
	{
		iter = g_AccUserRegList.begin();
		while ( iter != g_AccUserRegList.end() )
		{
			Ret=2;
			memcpy(&_theAccUserReg,&(*iter),sizeof(AccUserRegStruct) );
			memset(UName,0,sizeof(UName));
			memset(PWord,0,sizeof(PWord));
			memset(UNameB64,0,sizeof(UNameB64));
			memset(PWordB64,0,sizeof(PWordB64));
			memset(UNameB64URL,0,sizeof(UNameB64URL));
			memset(PWordB64URL,0,sizeof(PWordB64URL));
			memset(buf,0,sizeof(buf));
			memset(SendBuf,0,sizeof(SendBuf));
			memset(recrbuf,0,sizeof(recrbuf));
			memset(OutBuf,0,sizeof(OutBuf));

			strcpy(UName,_theAccUserReg.Acc_uname);
			strcpy(PWord,_theAccUserReg.Acc_passwd);
			int U=strlen(UName);
			int P=strlen(PWord);

			TeaEncrypt((unsigned char *)UName,U,0);
			TeaEncrypt((unsigned char *)PWord,P,0);
			B64.Encrypt(UName,U,UNameB64);
			B64.Encrypt(PWord,P,PWordB64);
			url_encode(UNameB64, strlen(UNameB64),UNameB64URL, &new_length);
			url_encode(PWordB64, strlen(PWordB64),PWordB64URL, &new_length);
			sprintf(buf,"method=adduser&uname=%s&upass=%s",UNameB64URL,PWordB64URL);
			http.PostData((unsigned char *)buf,strlen(buf));
			_log.WriteLog("AccUserReg SendBuf=%s\n",buf);
			int len=http.RecvData(recrbuf,1024);
			if ( len>0 )
			{
				int dlen=B64.Decrypt(recrbuf,len,OutBuf);
				TeaDecrypt((unsigned char*)OutBuf, dlen, 0);
				OutBuf[dlen]='\0';
				_log.WriteLog("AccUserReg OutBuf=%s\n",OutBuf);

				if(strcasestr(OutBuf,"result=0"))
					Ret=0;//printf("成功\n");
				else if(strcasestr(OutBuf,"result=1"))
					Ret=1;//printf("已经存在\n");
				else
					Ret=2;//printf("其他失败\n");
			}
			_theAccUserReg.RegRet = Ret;
			_log.WriteLog("AccUserReg name=%s,Ret=%d\n",_theAccUserReg.Acc_uname,Ret);

			if ( _theAccUserReg.m_nServID !=0 )
			{
				ServIpToThreaditer = g_mServIpToThread.find(_theAccUserReg.m_nServID);
				if ( ServIpToThreaditer != g_mServIpToThread.end() )
				{
					_theAccUserReg.m_nConnIndex = ServIpToThreaditer->second.nConnIndex;
					((CWorkThread*)ServIpToThreaditer->second.pWorkThread)->AddToUserRegReturnList(&_theAccUserReg);
				}
			}
			pthread_mutex_lock(&g_AccUserRegListlock);
			g_AccUserRegList.pop_front();
			pthread_mutex_unlock(&g_AccUserRegListlock);
			iter = g_AccUserRegList.begin();
		}
		usleep(20000);
	}
	return 0;
}
int AccUserReg::AddToList(AccUserRegStruct * pData)
{
	_log.WriteLog("AccUserReg::AddToList m_uname=%s,pw=%s\n",pData->Acc_uname,pData->Acc_passwd);

	pthread_mutex_lock(&g_AccUserRegListlock);
	AccUserRegStruct _theAccUserReg;
	memcpy(&_theAccUserReg,pData,sizeof(AccUserRegStruct));
	g_AccUserRegList.push_back(_theAccUserReg);
	pthread_mutex_unlock(&g_AccUserRegListlock);
	return 0;
}




