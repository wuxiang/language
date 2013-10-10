/***************************************************************
 * *
 * * make comment: the effective between string set and text
 * * use set is more effective than strcasestr(str), 3 times
 * *
 * ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

void compareF(const std::set<std::string>& sset, std::vector<std::string>& vSet)
{
	fprintf(stderr, "\n");
	struct timeval  start;
	gettimeofday(&start, NULL);
	std::vector<std::string>  vRes;
	std::vector<std::string>::iterator it = vSet.begin();
	while (it != vSet.end())
	{
		if (sset.find(*it) == sset.end())
		{
			fprintf(stderr, "%s ", it->c_str());
			vRes.push_back(*it);
		}
		++it;
	}
	struct timeval end;
	gettimeofday(&end, NULL);
	fprintf(stderr, "\nuse time: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
}

void compareFChar(const std::string& cSet, std::vector<std::string>& vSet)
{
	fprintf(stderr, "\n");
	struct timeval  start;
	gettimeofday(&start, NULL);
	std::vector<std::string>  vRes;
	std::vector<std::string>::iterator it = vSet.begin();
	const char* pSet = cSet.c_str();
	while (it != vSet.end())
	{
		if (!strcasestr(pSet, it->c_str()));
		{
			fprintf(stderr, "%s ", it->c_str());
			vRes.push_back(*it);
		}
		++it;
	}
	struct timeval end;
	gettimeofday(&end, NULL);
	fprintf(stderr, "\nuse time: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
}

int main()
{
	std::string  vStr;
	std::set<std::string>  sset;
	int  val = 300000;
	for (int i = 0; i < 100; ++i)
	{
		++val;
		char buf[32] = { 0 };
		sprintf(buf, "%d", val);
		sset.insert(std::string(buf));
		vStr += buf;
		vStr += ',';
	}

	srand(time(0));
	int rnd = 300000;
	int flag = 0;
	std::vector<std::string> vSet;
	for (int i = 0; i < 100; ++i, ++flag)
	{
		int  sum = rnd + random() % 1000;
		char buf[32] = { 0 };
		sprintf(buf, "%d", sum);
		vSet.push_back(std::string(buf));
		fprintf(stderr, "%d ", sum);
		if (flag == 9)
		{
			fprintf(stderr, "\n");
			flag = 0;
		}
	}
	compareF(sset, vSet);
	compareFChar(vStr, vSet);

	return 0;
}
