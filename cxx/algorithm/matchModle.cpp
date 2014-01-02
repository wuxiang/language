char *qsearch(char *text, int n, char *patt, int m)
{
	int i = 0;
    int tab_p[128] = {0};
    char *p = patt;
    char *temp_t, *t = text;

    if (n < 0)
    {
        n = strlen(text);
    }

    if (m < 0)
    {
        m = strlen(patt);
    }
    
    if (m == 0)
    {
        return text;
    }

    /* 构造移动表，假设字符都在0~127之间，即纯ASCII码 */
    for (i=0; i < 128; i++)
    {
        tab_p[i] = m + 1;
    }

    for (; *p; p++)
    {
        tab_p[*p] = m - (p - patt);
    }

    /* 开始移动查找 */
    while (t+m <= text+n)
    {
        for(p = patt, temp_t = t; *p != 0; p++,temp_t++)
        {
            if (*p != *temp_t)
            {
                break;
            }
        }
        
        if (*p == 0) /* 找到了 */
        {
            return t;
        }

        t += tab_p[*(t+m)];
    }

    return NULL;
}