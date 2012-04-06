#include <iostream>
#include <string>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

bool find_file_in_current_dir(const std::string& source, const std::string& name, std::string& des)
{
    boost::filesystem::path path(source);
    if (boost::filesystem::exists(path))
    {
        std::cout << "path is not exist" << std::endl;
        return false;
    }
    std::cout << path << std::endl;

    for (boost::filesystem::directory_iterator it(path); it != boost::filesystem::directory_iterator(); ++it)
    {
        if (boost::filesystem::is_regular_file(it->status()))
        {
            if (it->filename() == name)
            {
                std::cout << *it << std::endl;
                //des = it->path.string();
                return true;
            }
        }
    }
    return false;
}


bool get_path(const std::string& source, std::size_t layer,  const std::string& name, std::string& path)
{
    std::string src_path = source;

    if (src_path.empty())
    {
        return false;
    }

    if (*(source.rbegin()) != '/')
    {
        src_path += "/";
    }

    while (!find_file_in_current_dir(src_path, name, path))
    {
        if (layer > 0)
        {
            --layer;
            src_path += "../";
        }
        else
        {
            return false;
        }
    }
    return true;
}

void print_path(const boost::filesystem::path& path)
{
    std::cout << path << std::endl;

    boost::filesystem::path::iterator it;
    for (it = path.begin(); it != path.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

int main()
{
    boost::filesystem::path path = boost::filesystem::current_path();
    print_path(path);

    std::string result;
    std::string name("sizeof.c");
    get_path(path.string(), 4, name, result);

    return 0;
}
