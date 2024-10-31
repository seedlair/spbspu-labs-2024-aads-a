#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>
#include <stdexcept>

template<typename T>
class Queue
{
public:
    void push(const T& item)
    {
        elements.push_back(item);
    }

    void pop()
    {
        if (elements.empty())
            throw std::out_of_range("Queue<>::pop(): empty queue");
        elements.pop_front();
    }

    const T& front() const
    {
        if (elements.empty())
            throw std::out_of_range("Queue<>::front(): empty queue");
        return elements.front();
    }

    bool empty() const
    {
        return elements.empty();
    }

private:
    std::deque<T> elements;
};

#endif
