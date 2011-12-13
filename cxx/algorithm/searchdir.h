#ifndef _SEARCHDIR_H_
#define _SEARCHDIR_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <vector>
#include <string>
#include <map>

typedef struct List
{
    std::string  m_name;
    std::vector<List>  m_next;
}DirList;

class SearchDir
{
    private:
        typedef std::map<int, std::string>::iterator strIte;

        DirList     m_head;
        std::map<int, std::string>  formatString;

        bool searchRecur(DirList* plist);
        void insertRecord(const int deep, const std::string value);
        void format(const DirList& namelist, const int deep);
    public:
        SearchDir(const char*  path);
        ~SearchDir();
        void directoryTree();
};

//ftw fts may be more good
#endif //_SEARCHDIR_H_
