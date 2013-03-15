#ifndef _STFORTEST_H_
#define _STFORTEST_H_
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

const char* const  filename = "myfifotest";

struct  ftest
{
	int  a;
	int  b;
	char c;

	ftest(): a(0), b(0), c('\0')
	{
	}

	bool operator==(const ftest&  val)
	{
		return (a == val.a
			    && b == val.b
			    && c == val.c);
	}
};

struct stest
{
	uint32_t	len;
	char       content[100];

	stest(): len(0)
	{
		bzero((void*)content, 100);
	}

	bool operator==(const stest& val)
	{
		return (len == val.len
				&& (strcmp(content, val.content) == 0));
	}
};

struct ttest
{
	int  a;
	float b;
	double c;

	char  d[255];

	ttest(): a(0), b(0), c(0)
	{
		bzero(d, 255);
	}

	bool operator==(const ttest&  val)
	{
		return (a == val.a
				&& b == val.b
				&& c == val.c
				&& (strcmp(d, val.d) == 0));
	}
};

struct rtest
{
	ftest   amem;
	stest   bmem;
	ttest   cmem;

	rtest()
	{
	}

	bool operator==(const rtest& val)
	{
		return (amem == val.amem
				&& bmem == val.bmem
				&& cmem == val.cmem);
	}
};

#endif //_STFORTEST_H_
