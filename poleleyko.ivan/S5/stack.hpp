#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <stdexcept>

template<typename T>
class Stack
{
public:
    void push(const T& item)
    {
        elements.push_back(item);
    }

    void pop()
    {
        if (elements.empty())
            throw std::out_of_range("Stack<>::pop(): empty stack");
        elements.pop_back();
    }

    const T& top() const
    {
        if (elements.empty())
            throw std::out_of_range("Stack<>::top(): empty stack");
        return elements.back();
    }

    bool empty() const
    {
        return elements.empty();
    }

private:
    std::vector<T> elements;
};

#endif
