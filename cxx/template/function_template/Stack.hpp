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
    std::vector<T> elems;
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

//test number of template arguement when partial instantiation
template<typename T1, typename T2>
class s_map
{
    private:
        std::map<T1, T2> m_map;
    public:
        bool push(const T1& key, const T2& value);
        void pop();
};


template<typename T1, typename T2>
bool s_map<T1, T2>::push(const T1& key, const T2& value)
{
    return true;
}

template<typename T1, typename T2>
void s_map<T1, T2>::pop()
{
}

template<typename T>
class s_map<T, int>
//class s_map<T, int, int> error: template arguments (3, should be 2)
{
    private:
        std::map<T, int> m_map;
    public:
        bool push(const T& key, const int& value);
        void pop();
};


template<typename T>
//bool s_map<T>::push(const T& key, const int& value) error: template arguments (1, should be 2)
bool s_map<T, int>::push(const T& key, const int& value)
{
    return true;
}

template<typename T>
void s_map<T, int>::pop()
{
}
//template class specialization
template<>
class Stack<std::string>
{
private:
    std::deque<std::string> elems; //different from before
public:
    Stack()
    {
    }
    Stack(const Stack<std::string>& elm)
    {
        elems = elm.elems;
    }
    void push(const std::string& elm);
    void pop();
    std::string top() const;
    bool empty() const
    {
        return elems.empty();
    }
};

void Stack<std::string>::push(const std::string& elm)
{
    elems.push_back(elm);
}

void Stack<std::string>::pop()
{
    if(elems.empty())
    {
        throw std::out_of_range("Stack<>::pop empty stack");
    }
    elems.pop_back();
}

std::string  Stack<std::string>::top() const
{
    if(elems.empty())
    {
        throw std::out_of_range("Stack<>::top empty stack");
    }
    return elems.back();
}

//default template arguement
template<typename T, typename CONT = std::vector<T> >
class Stack_t
{
private:
    CONT elems; //different from before
public:
    Stack_t()
    {
    }
    Stack_t(const Stack_t<T>& elm)
    {
        elems = elm.elems;
    }
    void push(const T& elm);
    void pop();
    T top() const;
    bool empty() const
    {
        return elems.empty();
    }
};

template<typename T, typename CONT>
void Stack_t<T, CONT>::push(const T& elm)
{
    elems.push_back(elm);
}

template<typename T, typename CONT>
void Stack_t<T, CONT>::pop()
{
    if(elems.empty())
    {
        throw std::out_of_range("Stack_t<>::pop empty stack");
    }
    elems.pop_back();
}

template<typename T, typename CONT>
T  Stack_t<T, CONT>::top() const
{
    if(elems.empty())
    {
        throw std::out_of_range("Stack<>::top empty stack");
    }
    return elems.back();
}

//nontype template class parameters
template<typename T, int MAXSIZE>
class Stack_non
{
private:
    T      elems[MAXSIZE];
    int    numElems;
public:
    Stack_non();
    void push(const T& elm);
    void pop();
    T top() const;
    bool empty() const
    {
        return numElems == 0;
    }
    bool full() const
    {
        return numElems == MAXSIZE;
    }
};

template<typename T, int MAXSIZE>
Stack_non<T, MAXSIZE>::Stack_non(): numElems(0)
{
}

template<typename T, int MAXSIZE>
void Stack_non<T,  MAXSIZE>::push(const T& elm)
{
    if(numElems == MAXSIZE)
    {
        throw std::out_of_range("Stack_non<>::push: stack is full");
    }
    elems[numElems] = elm;
    ++numElems;
}

template<typename T, int MAXSIZE>
void Stack_non<T, MAXSIZE>::pop()
{
    if(numElems <= 0)
    {
        throw std::out_of_range("Stack_non<>::pop empty stack");
    }
    --numElems;
}

template<typename T, int MAXSIZE>
T  Stack_non<T, MAXSIZE>::top() const
{
    if(numElems <= 0)
    {
        throw std::out_of_range("Stack_non<>::pop empty stack");
    }
    return elems[numElems - 1];
}
#endif //_STACK_HPP_

