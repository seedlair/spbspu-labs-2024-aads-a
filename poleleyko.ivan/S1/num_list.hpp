#ifndef NUM_LIST_HPP
#define NUM_LIST_HPP

#include <iterator>
#include <list>
#include <iostream>

namespace poleleyko
{
  template<typename T>
  class List : public std::list<T> {};

  using ListOfSizes = List<size_t>;
}

#endif
