#include <iostream>
#include <stdlib.h>
#include <string.h>

bool  find_substr(const char* src, const  char* dest)
{
	if (src == NULL || dest == NULL)
	{
		return false;
	}

	const char* pBeginSrc = src;
	int  lenSrc = strlen(src);
	int  lenDest = strlen(dest);
	int  lenCurrent = 0;

	while (pBeginSrc)
	{
		if (lenSrc - lenCurrent < lenDest)
		{
			break;
		}

		++lenCurrent;
		if (*pBeginSrc++ != *dest)
		{
			continue;
		}
		else
		{
			const char* pTemp = pBeginSrc - 1;
			if (!strncmp(pTemp, dest, lenDest))
			{
				return true;
			}
		}
	}

	return false;
}

int main()
{
	const char* ch = "skdajfklasjfkldsjafkljksajfjeionvaief";
	const char* ch2 = "1234";
	if (find_substr(ch, ch2))
	{
		std::cout << "have find child string" << std::endl;
	}
	return 0;
}
