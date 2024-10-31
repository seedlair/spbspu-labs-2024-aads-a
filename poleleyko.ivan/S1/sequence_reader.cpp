#include "sequence_reader.hpp"

void poleleyko::readSequence(std::istream& inputStream, SequenceList& sequenceList)
{
  std::string lineData = "";
  inputStream >> lineData;
  
  while (inputStream)
  {
    sequenceList.push_front({lineData, List<size_t>{}});
    
    while (inputStream >> lineData)
    {
      try
      {
        size_t parsedNumber = std::stoull(lineData);
        sequenceList.front().second.push_front(parsedNumber);
      }
      catch (const std::invalid_argument&)
      {
        break;
      }
    }
  }
}
