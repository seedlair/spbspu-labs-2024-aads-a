#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <algorithm>
#include <iterator>

namespace poleleyko  // Изменено пространство имен
{
    template<typename Comparator, typename Iterator>
    void selectionSort(Iterator start, Iterator finish, Comparator cmp)
    {
        for (Iterator current = start; current != finish; ++current)
        {
            Iterator minimum = current;
            for (Iterator next = current; next != finish; ++next)
            {
                if (cmp(*next, *minimum))
                {
                    minimum = next;
                }
            }
            std::swap(*current, *minimum);
        }
    }

    template<typename Comparator, typename Iterator>
    void mergeInPlace(Iterator first, Iterator mid, Iterator last, Comparator cmp)
    {
        while (first != mid && mid != last)
        {
            if (cmp(*mid, *first))
            {
                std::rotate(first, mid, std::next(mid));
                ++mid;
            }
            else
            {
                ++first;
            }
        }
    }

    template<typename Comparator, typename Iterator>
    void mergeSort(Iterator start, Iterator finish, Comparator cmp)
    {
        auto length = std::distance(start, finish);
        if (length > 1)
        {
            Iterator mid = start;
            std::advance(mid, length / 2);
            mergeSort(start, mid, cmp);
            mergeSort(mid, finish, cmp);
            mergeInPlace(start, mid, finish, cmp);
        }
    }
}

#endif
