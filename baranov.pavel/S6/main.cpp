#include <iostream>
#include <cstddef>
#include <string>
#include <functional>
#include <utility>
#include <deque>
#include <list/list.hpp>
#include "sortings.hpp"
#include "testSortings.hpp"
#include "generate.hpp"

int main(int argc, char * argv[])
{
  using namespace baranov;
  if (argc < 4)
  {
    std::cerr << "Incorrect CLA\n";
    return 1;
  }
  try
  {
    std::string direction = argv[1];
    std::string type = argv[2];
    std::pair< std::string, std::string > params{direction, type};

    testSortings< float >(std::cout, 10, std::less< float >());
    std::cout << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

