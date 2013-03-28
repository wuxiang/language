#include "globFunc.h"

/*
*  Pack binary data into a string
*
* (output)  c   : result buffer,must bigger than PASS_MD5 * 2 bytes
* (intput)  ptr : binary buffer
* (inputt)  sz  : binary buffer's length
*/
void Bin2Str(char *c, void *ptr, int sz) {
	static char hex[17] = "0123456789abcdef";
	unsigned char *u = (unsigned char *) ptr;
	const unsigned char *eu =  u + sz;
	register unsigned char uu;
	for (; u != eu; ++u) {
		uu = *u;
		*(c++) = hex[(uu & 0xf0) >> 4];
		*(c++) = hex[uu & 0xf];
	}
}

/*
* Unpack binary data from a string
*
* (output)  c   : result buffer,must bigger than PASS_MD5 bytes
* (intput)  ptr : hex buffer
* (inputt)  sz  : hex buffer's length
*/
void Str2Bin(char *c, void *ptr, int sz)
{
	register unsigned char uu = 0;
	register int d;
	unsigned char *u = (unsigned char *) ptr;
	const unsigned char *eu =  u + sz;
	for (; u != eu; ++u) {
		d = *(c++);
		if ((d >= '0') && (d <= '9'))
			uu = ((d - '0') << 4);
		else if ((d >= 'a') && (d <= 'f'))
			uu = ((d - ('a'-10)) << 4);
		d = *(c++);
		if ((d >= '0') && (d <= '9'))
			uu |= (d - '0');
		else if ((d >= 'a') && (d <= 'f'))
			uu |= (d - ('a'-10));
		*u = uu;
	}

}

inline int PassCMP(char *pass_md5_str, char *passwd)
{
	char result[PASS_MD5] = {0};
	char result_str[PASS_MD5 * 2 + 1 ] = {0};
	md5_signature((unsigned char*)(passwd), strlen(passwd) , (unsigned char*) result);

	Bin2Str(result_str, result, PASS_MD5);
	return strncmp(pass_md5_str, result_str, PASS_MD5 * 2);
}

