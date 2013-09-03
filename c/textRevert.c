#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void revert(char* start, char* end)
{
	while (start < end)
	{
		char temp = *start;
		*start = *end;
		*end = temp;
		++start;
		--end;
	}
}

int main()
{
	char  text[] = {"hello i am a student"};
	//text[5] = 'm';
	char*  start = text;
	char*  end = text;
	while (*start != '\0')
	{
		if (*end == ' ' || *end == '\0')
		{
			revert(start, end - 1);
			if (*end == '\0')
			{
				break;
			}
			start = ++end;
		}
		else
		{
			++end;
		}
	}
	printf("length = %d\n", strlen(text));
	printf("value = %s\n", text);
	return 0;
}
