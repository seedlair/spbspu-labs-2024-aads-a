#ifndef SORTPROCESS_HPP
#define SORTPROCESS_HPP

#include <iostream>
#include <list>
#include <deque>
#include <random>

#include <custom_list.hpp>  // Изменено на более общее имя

#include "sorting_algorithms.hpp"  // Изменено на более общее имя

namespace poleleyko  // Изменено пространство имен
{
    template <typename Container>
    void displayContainer(const Container& container, std::ostream& out)
    {
        auto it = container.cbegin();
        out << *it;
        for (auto it = ++container.cbegin(); it != container.cend(); ++it)
        {
            out << " " << *it;
        }
        out << "\n";
    }

    template <typename T, typename Comparator>
    void processSorting(size_t size, std::ostream& out)
    {
        std::deque<T> dataQueue;
        List<T> customList;
        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());
        std::uniform_real_distribution<> distribution(-1000.0, 1000.0);
        
        for (size_t i = 0; i < size; ++i)
        {
            auto value = static_cast<T>(distribution(generator));
            dataQueue.push_back(value);
            customList.push_front(value);
        }

        std::list<T> biList(dataQueue.cbegin(), dataQueue.cend());
        std::list<T> mergeList(dataQueue.cbegin(), dataQueue.cend());
        std::deque<T> sortedDeque(dataQueue.cbegin(), dataQueue.cend());
        std::deque<T> selectionDeque(dataQueue.cbegin(), dataQueue.cend());
        std::deque<T> mergeDeque(dataQueue.cbegin(), dataQueue.cend());

        selectionSort(biList.begin(), biList.end(), Comparator());
        mergeSort(mergeList.begin(), mergeList.end(), Comparator());
        std::sort(sortedDeque.begin(), sortedDeque.end(), Comparator());
        selectionSort(selectionDeque.begin(), selectionDeque.end(), Comparator());
        mergeSort(mergeDeque.begin(), mergeDeque.end(), Comparator());
        selectionSort(customList.begin(), customList.end(), Comparator());

        displayContainer(dataQueue, out);
        displayContainer(customList, out);
        displayContainer(biList, out);
        displayContainer(selectionDeque, out);
        displayContainer(sortedDeque, out);
        displayContainer(mergeDeque, out);
        displayContainer(mergeList, out);
    }
}

#endif
