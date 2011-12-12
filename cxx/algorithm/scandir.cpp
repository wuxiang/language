#define _SVID_SOURCE
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <error.h>
#include <stdlib.h>
#include <iostream>
#include "searchdir.h"

int main()
{
    struct dirent** namelist;
    int n = scandir("../../", &namelist, NULL, alphasort);
    if (n < 0)
    {
        perror("scandir\n");
    }
    else
    {
        while(n--)
        {
            printf("%s\n", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }

    printf("\n++++++++++++++++++++++++++\n");
    DIR* pd = opendir("../..");
    struct dirent* entry = NULL;
    while((entry=readdir(pd)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }

    printf("\n++++++++++++++readdir++++++++++++\n");
    SearchDir  dir("../..");    
    dir.directoryTree();
    return 0;
}

