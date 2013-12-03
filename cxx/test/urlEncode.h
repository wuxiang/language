#ifndef URLENCODE_H_
#define URLENCODE_H_
namespace HttpUtility
{

    typedef unsigned char BYTE;

    inline BYTE toHex(const BYTE &x)
    {
        return x > 9 ? x -10 + 'A': x + '0';
    }

    inline BYTE fromHex(const BYTE &x)
    {
        return isdigit(x) ? x-'0' : x-'A'+10;
    }

    inline string URLEncode(const string &sIn)
    {
        string sOut;
        for( size_t ix = 0; ix < sIn.size(); ix++ )
        {
            BYTE buf[4];
            memset( buf, 0, 4 );
            if( isalnum( (BYTE)sIn[ix] ) )
            {
                buf[0] = sIn[ix];
            }
            //else if ( isspace( (BYTE)sIn[ix] ) ) //貌似把空格编码成%20或者+都可以
            //{
            //    buf[0] = '+';
            //}
            else
            {
                buf[0] = '%';
                buf[1] = toHex( (BYTE)sIn[ix] >> 4 );
                buf[2] = toHex( (BYTE)sIn[ix] % 16);
            }
            sOut += (char *)buf;
        }
        return sOut;
    };

    inline string URLDecode(const string &sIn)
    {
        string sOut;
        for( size_t ix = 0; ix < sIn.size(); ix++ )
        {
            BYTE ch = 0;
            if(sIn[ix]=='%')
            {
                ch = (fromHex(sIn[ix+1])<<4);
                ch |= fromHex(sIn[ix+2]);
                ix += 2;
            }
            else if(sIn[ix] == '+')
            {
                ch = ' ';
            }
            else
            {
                ch = sIn[ix];
            }
            sOut += (char)ch;
        }
        return sOut;
    }

	inline bool hasChineseCharacter(const std::string&  str)
	{
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (str[i] <= 0 || str[i] >= 127)
			{
				return true;
			}

		}

		return false;
	}

	inline bool hasChineseCharacter(const char*  str)
	{
		int len = strlen(str);
		for (int i = 0; i < len; ++i)
		{
			if (str[i] <= 0 || str[i] >= 127)
			{
				return true;
			}
		}

		return false;
	}

	inline bool isUtf8String(const char* str, int length)
	{
		int i = 0;
		int nBytes = 0;
		unsigned char chr = 0;
		bool bAllAscii = true;

		while (i < length)
		{
			chr = *(str + i);
			if ((chr & 0x80 != 0))
			{
				bAllAscii = false;
			}

			if (nBytes == 0)
			{
				if ((chr & 0x80) != 0)
				{
					while ((chr & 0x80) != 0)
					{
						 chr <<= 1;
						 nBytes++;
					}

					if (nBytes < 2 || nBytes > 6)
					{
						return false;
					}

					nBytes--;
				}
			}
			else
			{
				if ((chr & 0xc0) != 0x80)
				{
					return false;
				}

				nBytes--;
			}
			++i;
		}

		if (bAllAscii)
		{
			return false;
		}

		return (nBytes == 0);
	}
}

#endif //URLENCODE_H_
