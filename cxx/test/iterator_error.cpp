#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> vec;   
    std::list<int>  list;
    for(int i=0;i<10;i++)   
    {
        vec.push_back(i);   
        list.push_back(i);
    }

    // vector
    std::vector<int>::iterator ite = vec.begin();
    std::advance(ite, 5);

    std::vector<int>::iterator it1 = vec.begin();
    std::advance(it1, 2);
    std::cout << *ite << std::endl;
    vec.erase(it1);
    std::cout << *ite << std::endl;

    // list
    std::list<int>::iterator lt = list.begin();
    std::advance(lt, 5);
    std::list<int>::iterator lt1 = list.begin();
    std::advance(lt1, 2);
    std::list<int>::iterator lt2 = list.begin();
    std::advance(lt2, 1);

    std::cout << *lt << std::endl;
    list.erase(lt1);
    std::cout << *lt << std::endl;
    list.erase(lt2);
    std::cout << *lt << std::endl;

    // invalid iterator == end()
    vec.clear();
    if (ite == vec.end())
    {
        std::cout << "end" << std::endl;
    }
    else
    {
        std::cout << "non-end" << std::endl;
    }

    list.erase(lt);
    //list.clear();
    if (lt == list.end())
    {
        std::cout << "end" << std::endl;
    }
    else
    {
        std::cout << "non-end" << std::endl;
    }

    //std::cout<<"capacity:"<<vec.capacity()<<std::endl;//查看预分配空间大小   
    //std::vector<int>::iterator iter =vec.begin()+2;   
    //vec.insert(iter,100);
    //std::cout<<"capacity:"<<vec.capacity()<<std::endl;     
    //std::cout<<*iter<<std::endl;   
    //for(std::vector<int>::iterator it=vec.begin();it!=vec.end();it++)   
    //    std::cout<<*it<<std::endl;  
    return 0;
}
