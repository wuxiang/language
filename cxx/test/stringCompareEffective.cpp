/*******************************************************
**
**make a experiment, the effective between string operator== and strcmp
**result string operator== is 3.4 times faster than strcmp
**
********************************************************/
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void compareF(const std::set<std::string>& sset, std::vector<std::string>& vSet)
{
	fprintf(stderr, "\n");
	struct timeval  start;
	gettimeofday(&start, NULL);
	std::vector<std::string>  vRes;
	std::vector<std::string>::iterator it = vSet.begin();
	while (it != vSet.end())
	{
		if (*(sset.begin()) == *it)
		{
			vRes.push_back(*it);
		}
		++it;
	}
	struct timeval end;
	gettimeofday(&end, NULL);
	fprintf(stderr, "\noperator== use time: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
}

void compareFF(const std::set<std::string>& sset, std::vector<std::string>& vSet)
{
	fprintf(stderr, "\n");
	struct timeval  start;
	gettimeofday(&start, NULL);
	std::vector<std::string>  vRes;
	std::vector<std::string>::iterator it = vSet.begin();
	while (it != vSet.end())
	{
		if (strcmp((sset.begin())->c_str(), it->c_str()))
		{
			vRes.push_back(*it);
		}
		++it;
	}
	struct timeval end;
	gettimeofday(&end, NULL);
	fprintf(stderr, "\nstrcmp use time: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
}

int main()
{
	std::set<std::string>  sset;
	int  val = 300000;
	for (int i = 0; i < 100; ++i)
	{
		++val;
		char buf[32] = { 0 };
		sprintf(buf, "%d", val);
		sset.insert(std::string(buf));
	}

	srand(time(0));
	int rnd = 300000;
	std::vector<std::string> vSet;
	for (int i = 0; i < 100; ++i)
	{
		int  sum = rnd + random() % 1000;
		char buf[32] = { 0 };
		sprintf(buf, "%d", sum);
		vSet.push_back(std::string(buf));
	}

	compareF(sset, vSet);
	compareFF(sset, vSet);
	return 0;
}
