#include <iostream>
#include <string>

#include <stdio.h>
#include <unistd.h>

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

const std::string path = "num.txt";

class executor
{
    public:
        void operator()()
        {
            uint64_t total = 0;
            for(uint64_t i = 0; i < 10000; ++i)
            {
                total += recurse(i);
            }
        }

    private:
        uint64_t recurse(const uint64_t num)
        {
            if (0 == num)
            {
                return 1;
            }

            return (num * recurse(num - 1));
        }
};

void twrite()
{
    boost::shared_ptr<FILE> pFile(fopen(path.c_str(), "w+"), fclose);
    if (!pFile)
    {
        return;
    }

    for (int i = 0; i < 100000000; ++i)
    {
        fwrite((void*)(&i), sizeof(i), 1, pFile.get());
    }

    fflush(pFile.get());
}

void tread()
{
    boost::shared_ptr<FILE> pFile(fopen(path.c_str(), "w+"), fclose);
    int flag = 0;
    int res = 0;
    while(fread(&res, sizeof(res), 1, pFile.get()))
    {
        ++flag;
        printf("%d\t", res);
        if (flag == 8)
        {
            printf("\n");
            flag = 0;
        }
    }
}

int main()
{
    executor exe;
    boost::thread  th(exe);
    twrite();
    tread();
    th.join();
    return 0;
}
