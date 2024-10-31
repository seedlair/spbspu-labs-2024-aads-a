#ifndef SEQUENCE_READER_HPP
#define SEQUENCE_READER_HPP

#include <string>
#include <istream>
#include "num_list.hpp"

namespace poleleyko
{
  using SequenceList = List< std::pair< std::string, List< size_t > > >;

  void readSequence(std::istream& inputStream, SequenceList& sequenceList);
}

#endif
