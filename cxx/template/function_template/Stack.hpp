#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <vector>
#include <string>
#include <deque>
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
#endif //_STACK_HPP_

