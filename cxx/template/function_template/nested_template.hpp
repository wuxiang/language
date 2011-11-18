#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <stdexcept>

template<typename T>
class Stack
{
private:
    std::deque<T> elems;
public:
    Stack()
    {
    }
    Stack(const Stack<T>& s)
    {
        elems = s.elems;
    }
    void push(const T& elm);
    void pop();
    T top() const;
    bool empty() const
    {
        return elems.empty();
    }

    template<typename T2>
    Stack<T>& operator=(const Stack<T2>& eql);
};

template<typename T>
void Stack<T>::push(const T& elm)
{
    elems.push_back(elm);
}

template<typename T>
void Stack<T>::pop()
{
    if(elems.empty())
    {
        throw std::out_of_range("Stack<>::pop empty stack");
    }
    elems.pop_back();
}

template<typename T>
T  Stack<T>::top() const
{
    if(elems.empty())
    {
        throw std::out_of_range("Stack<>::top empty stack");
    }
    return elems.back();
}

template<typename T>
template<typename T2>
Stack<T>& Stack<T>::operator=(const Stack<T2>& eql)
{
    if((void*)this = (void*)&eql)
    {
        return this;
    }

    Stack<T2> tmp(eql);
    elems.clear();

    while(!eql.empty())
    {
        elems.push_front(tmp.top());
        tmp.pop();
    }
    return *this;
}


//template template arguement
//template <typename T, template<typename ELEM, typename = std::allocator<ELEM> > class CONT = std::deque >
//class nest_nest_Stack
//{
//    private:
//        CONT<T> elems;
//    public:
//    void push(const T& elm);
//    void pop();
//    T top() const;
//    bool empty() const
//    {
//        return elems.empty();
//    }
//
//    template <typename T2, template<typename ELEM2, typename = std::allocator<ELEM2> > class CONT2>
//        nest_Stack<T, CONT>& operator= (const nest_Stack<T2, CONT2>& elq);
//};
//
//template<typename T, template<typename, typename> class CONT>
//void nest_Stack<T, CONT>::push(const T& elm)
//{
//    elems.push_back(elm);
//}
//
//template<typename T, template<typename, typename> class CONT>
//void nest_Stack<T, CONT>::pop()
//{
//    if(elems.empty())
//    {
//        throw std::out_of_range("nest_Stack<>::pop empty stack");
//    }
//    elems.pop_back();
//}
//
//template<typename T, template<typename, typename> class CONT>
//T  nest_Stack<T, CONT>::top() const
//{
//    if(elems.empty())
//    {
//        throw std::out_of_range("nest_Stack<>::top empty stack");
//    }
//    return elems.back();
//}
//
//template<typename T, template<typename, typename> class CONT>
//    template<typename T2, template<typename, typename> class CONT2>
//        nest_Stack<T, CONT>& nest_Stack<T, CONT>::operator=(const nest_Stack<T2, CONT2>& elq)
//{
//    if((void*)this == (void*)&elq)
//    {
//        return *this;
//    }
//
//    nest_Stack<T2, CONT2> tmp(elq);
//
//    elems.clear();
//    while (!tmp.empty())
//    {
//        elems.push_front(tmp.top());
//        tmp.pop();
//    }
//    return *this;
//}
#endif //_STACK_HPP_
