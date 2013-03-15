#include "correctTest.h"

CorrectForFixF::CorrectForFixF(const int tag): m_tag(tag)
{
	bzero((void*)m_mem,  10 * sizeof(struct ftest));
}

void CorrectForFixF::write()
{
	for (int i = 0; i < 10; ++i)
	{
		m_mem[i].a = i;
		m_mem[i].b = i;
		m_mem[i].b = 'a' + i;
	}

	GWFifo   fifo(filename, strlen(filename));
	for (int i = 0; i < 10; ++i)
	{
		fifo.set(m_tag, (void*)(m_mem + i), sizeof(struct ftest));
	}
}

void CorrectForFixF::read()
{
	GWFifo   fifo(filename, strlen(filename));
	int len = sizeof(struct ftest);
	int realLen = len;
	int tagT = 0;
	for (int i = 0; i < 10; ++i)
	{
		fifo.get(&tagT, (void*)(m_mem + i), &realLen);
		assert(len == realLen);
		assert(tagT == m_tag);
	}
}

void CorrectForFixF::wrrd()
{
	for (int i = 0; i < 10; ++i)
	{
		m_mem[i].a = i;
		m_mem[i].b = i;
		m_mem[i].b = 'a' + i;
	}

	GWFifo   fifo(filename, strlen(filename));
	for (int i = 0; i < 10; ++i)
	{
		fifo.set(m_tag, (void*)(m_mem + i), sizeof(struct ftest));
	}

	int len = sizeof(struct ftest);
	int realLen = len;
	int tagT = 0;
	for (int i = 0; i < 10; ++i)
	{
		fifo.get(&tagT, (void*)(m_rmem + i), &realLen);
		assert(len == realLen);
		assert(tagT == m_tag);
	}

	for (int i = 0; i < 10; ++i)
	{
		assert(m_mem[i] == m_rmem[i]);
	}
}

bool CorrectForFixF::operator==(const CorrectForFixF&  arg)
{
	bool res = true;;
	for (int i = 0; i < 10; ++i)
	{
		res = res && (m_mem[i] == arg.m_mem[i]);

		if (!res)
		{
			break;
		}
	}

	return res;
}

/************************************************/
CorrectForFixS::CorrectForFixS(const int tag): m_tag(tag)
{
	bzero((void*)m_mem,  10 * sizeof(struct stest));
}

void CorrectForFixS::write()
{
	const char*  const cst = "hello";
	for (int i = 0; i < 10; ++i)
	{
		m_mem[i].len =  i;
		strncpy(m_mem[i].content, cst, strlen(cst));
	}

	GWFifo   fifo(filename, strlen(filename));
	for (int i = 0; i < 10; ++i)
	{
		fifo.set(m_tag, (void*)(m_mem + i), sizeof(struct stest));
	}
}

void CorrectForFixS::read()
{
	GWFifo   fifo(filename, strlen(filename));

	int len = sizeof(struct stest);
	int realLen = len;
	int tagT = 0;
	for (int i = 0; i < 10; ++i)
	{
		fifo.get(&tagT, (void*)(m_mem + i), &realLen);
		assert(len == realLen);
		assert(tagT == m_tag);
	}
}

bool CorrectForFixS::operator==(const CorrectForFixS&  arg)
{
	bool res = true;
	for (int i = 0; i < 10; ++i)
	{
		res = res && (m_mem[i] == arg.m_mem[i]);

		if (!res)
		{
			break;
		}
	}

	return res;
}

/************************************************/
CorrectForFixT::CorrectForFixT(const int tag): m_tag(tag)
{
	bzero((void*)m_mem,  10 * sizeof(struct ttest));
}

void CorrectForFixT::write()
{
	for (int i = 0; i < 10; ++i)
	{
		m_mem[i].a =  i;
		m_mem[i].b =  1.02 + i;
		m_mem[i].c =  8.96 + 1;
	}

	GWFifo   fifo(filename, strlen(filename));
	for (int i = 0; i < 10; ++i)
	{
		fifo.set(m_tag, (void*)(m_mem + i), sizeof(struct ttest));
	}
}

void CorrectForFixT::read()
{
	GWFifo   fifo(filename, strlen(filename));

	int len = sizeof(struct ttest);
	int realLen = len;
	int tagT = 0;
	for (int i = 0; i < 10; ++i)
	{
		fifo.get(&tagT, (void*)(m_mem + i), &realLen);
		assert(len == realLen);
		assert(tagT == m_tag);
	}
}

bool CorrectForFixT::operator==(const CorrectForFixT&  arg)
{
	bool res = true;
	for (int i = 0; i < 10; ++i)
	{
		res = res && (m_mem[i] == arg.m_mem[i]);

		if (!res)
		{
			break;
		}
	}

	return res;
}

/************************************************/
CorrectForFixR::CorrectForFixR(const int tag): m_tag(tag)
{
	bzero((void*)m_mem,  10 * sizeof(struct rtest));
}

void CorrectForFixR::write()
{
	const char*  const cst = "hello";

	for (int i = 0; i < 10; ++i)
	{
		m_mem[i].amem.a = i;
		m_mem[i].amem.b = i;
		m_mem[i].amem.b = 'a' + i;

		m_mem[i].bmem.len =  i;
		strncpy(m_mem[i].bmem.content, cst, strlen(cst));

		m_mem[i].cmem.a =  i;
		m_mem[i].cmem.b =  1.02 + i;
		m_mem[i].cmem.c =  8.96 + 1;
	}

	GWFifo   fifo(filename, strlen(filename));
	for (int i = 0; i < 10; ++i)
	{
		fifo.set(m_tag, (void*)(m_mem + i), sizeof(struct rtest));
	}
}

void CorrectForFixR::read()
{
	GWFifo   fifo(filename, strlen(filename));

	int len = sizeof(struct rtest);
	int realLen = len;
	int tagT = 0;
	for (int i = 0; i < 10; ++i)
	{
		fifo.get(&tagT, (void*)(m_mem + i), &realLen);
		assert(len == realLen);
		assert(m_tag == tagT);
	}
}

bool CorrectForFixR::operator==(const CorrectForFixR&  arg)
{
	bool res = true;
	for (int i = 0; i < 10; ++i)
	{
		res = res && (m_mem[i] == arg.m_mem[i]);

		if (!res)
		{
			break;
		}
	}

	return res;
}

void WrRdRightNow::run()
{
	CorrectForFixF  wvar1(1);
	CorrectForFixS  wvar2(1);
	CorrectForFixT  wvar3(1);
	CorrectForFixR  wvar4(1);
	////var1.wrrd();
	wvar1.write();
	wvar2.write();
	wvar3.write();
	wvar4.write();

	CorrectForFixF  rvar1(1);
	CorrectForFixS  rvar2(1);
	CorrectForFixT  rvar3(1);
	CorrectForFixR  rvar4(1);
	rvar1.read();
	rvar2.read();
	rvar3.read();
	rvar4.read();

	assert(wvar1 == rvar1);
	assert(wvar2 == rvar2);
	assert(wvar3 == rvar3);
	assert(wvar4 == rvar4);

	printf("++++++++++++++write and read right success++++++++++++++++++\n");
}

