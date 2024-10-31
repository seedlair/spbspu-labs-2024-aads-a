#include <iostream>
#include <limits>

#include "sequence_reader.hpp"
#include "num_list.hpp" 

int main()
{
  using namespace poleleyko;
  SequenceList sequences;
  
  readSequence(std::cin, sequences);

  if (sequences.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  sequences.reverse();
  std::cout << sequences.front().first;

  for (auto it = ++sequences.cbegin(); it != sequences.cend(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";

  bool overflowDetected = false;
  size_t sum = 0;
  size_t offset = 0;
  bool hasData = true;
  ListOfSizes listOfSums;

  while (hasData)
  {
    hasData = false;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      auto numItr = it->second.cbegin();
      for (size_t skipCount = 0; skipCount < offset; ++skipCount)
      {
        if (numItr != it->second.cend())
        {
          ++numItr;
        }
      }
      if (numItr != it->second.cend())
      {
         if (hasData)
         {
           std::cout << " ";
         }
         if (std::numeric_limits<size_t>::max() - sum >= *numItr)
         {
           sum += *numItr;
         }
         else
         {
           overflowDetected = true;
         }
         std::cout << *numItr;
         hasData = true;
      }
    }
    if (hasData)
    {
      std::cout << "\n";
      listOfSums.push_front(sum);
      sum = 0;
    }
    ++offset;
  }
  if (overflowDetected)
  {
    std::cerr << "Overflow detected\n";
    return 1;
  }
  if (listOfSums.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  listOfSums.reverse();
  std::cout << listOfSums.front();
  for (auto it = ++listOfSums.cbegin(); it != listOfSums.cend(); ++it)
  {
    std::cout << " " << *it;
  }
  std::cout << "\n";
  return 0;
}
