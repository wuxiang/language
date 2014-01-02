#include <string>
#include <stdio.h>
struct  UserRelation
{
	std::string   uname;
	std::string   macIP;
	std::string   mobile;
	std::string   pushID;
	uint8_t       platform;
};

int main()
{
	UserRelation    uInfo;
	uInfo.uname.assign("wuxiang");
	uInfo.macIP.assign("10.10.10.10");
	uInfo.mobile.assign("13787913413");
	uInfo.pushID.assign("Android");
	uInfo.platform = 2;
	std::string  url("www.gw.com.cn");
	if (url[url.length() - 1] != '/')
	{
		url += '/';
	}
	char buf[2048] = { 0 };
	sprintf(buf, "%sAccservice/AccServlet.do?method=userkeybind&uname=%s", url.c_str(), uInfo.uname.c_str());
	if (uInfo.mobile.length())
	{
		sprintf(buf + strlen(buf), "&key=mobile=%s", uInfo.mobile.c_str());
	}
	sprintf(buf + strlen(buf), "&key=deviceid=%s", uInfo.macIP.c_str());

	if (uInfo.pushID.length())
	{
		sprintf(buf + strlen(buf), "&key=pushid=%s&key=platform=%d", uInfo.pushID.c_str(), uInfo.platform);
	}

	fprintf(stderr, "%s\n", buf);
	return 0;
}
