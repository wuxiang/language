#ifndef  _CORRECTTEST_H_
#define  _CORRECTTEST_H_
#include "stForTest.h"
#include "GWFifo.h"

// fix size struct
class  CorrectForFixF
{
public:
	CorrectForFixF(const int  tag);
	void write();
	void read();
	void wrrd();
	bool operator==(const CorrectForFixF&  arg);

private:
	int       m_tag;
	ftest     m_mem[10];
	ftest     m_rmem[10];
};

class  CorrectForFixS
{
public:
	CorrectForFixS(const int tag);
	bool operator==(const CorrectForFixS&  arg);
	void write();
	void read();

private:
	int       m_tag;
	stest     m_mem[10];
};

class  CorrectForFixT
{
public:
	CorrectForFixT(const int ta);
	bool operator==(const CorrectForFixT&  arg);
	void write();
	void read();

private:
	int       m_tag;
	ttest     m_mem[10];
};

class  CorrectForFixR
{
public:
	CorrectForFixR(const int tag);
	bool operator==(const CorrectForFixR&  arg);
	void write();
	void read();

private:
	int       m_tag;
	rtest     m_mem[10];
};

class WrRdRightNow
{
public:
	void run();
};

#endif //_CORRECTTEST_H_

