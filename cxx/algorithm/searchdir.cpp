#include "searchdir.h"

SearchDir::SearchDir(const char*  path)
{
    m_head.m_name = path;

    //get detail information of directory
    searchRecur(&m_head);
}

SearchDir::~SearchDir()
{
}

bool SearchDir::searchRecur(DirList* plist)
{
    DIR* dp = NULL;
    if((dp = opendir(plist->m_name.c_str())) == NULL)
    {
        fprintf(stderr, "can not open directory: %s\n", m_head.m_name.c_str());
        return false;
    }

    if ( -1 == chdir(plist->m_name.c_str()))
    {
        fprintf(stderr, "change work directory failed\n");
        closedir(dp);
        return false;
    }

    struct dirent* entry = NULL;
    struct stat   statbuf;
    while((entry = readdir(dp)) != NULL)
    {
        DirList newelement; //for store next directory or file
        newelement.m_name = entry->d_name;

        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            if (strcmp(".", entry->d_name) == 0 ||
                strcmp("..", entry->d_name) == 0 ||
                strcmp(".git", entry->d_name) ==0)
            {
                newelement.m_next.clear();
                plist->m_next.push_back(newelement);
                continue;
            }
            this->searchRecur(&newelement);
            plist->m_next.push_back(newelement);
        }
        else
        {
            newelement.m_next.clear();
            plist->m_next.push_back(newelement);
        }
    }
    chdir("..");
    closedir(dp);
}

void SearchDir::insertRecord(const int deep, const std::string value)
{
    strIte ite = formatString.find(deep);
    if (ite == formatString.end())
    {
        formatString.insert(std::make_pair(deep, value));
    }
    else
    {
        ite->second += " " + value;
    }
}

void SearchDir::format(const DirList& namelist, const int deep)
{
    if (0 == namelist.m_next.size())
    {
        this->insertRecord(deep, namelist.m_name);
        return;
    }

    this->insertRecord(deep, namelist.m_name);

    for ( std::size_t index = 0; index < namelist.m_next.size(); ++index)
    {
        this->format(namelist.m_next[index], deep + 1);
    }
}

void SearchDir::directoryTree()
{
    std::cout << std::string(100, '=') << std::endl;
    this->format(m_head, 0);
    for (strIte ite = formatString.begin(); ite != formatString.end(); ++ite)
    {
        std::cout << ite->second << std::endl;
    }
}


