#include "outputResult.hpp"
#include "iostream"

void zakozhurnikova::outputResult(zakozhurnikova::Stack< ll >& result)
{
  unsigned long long quantity = 0;
  while(!result.empty())
  {
    if(quantity != 0)
    {
      std::cout << " ";
    }
    std::cout << result.top();
    result.drop();
    ++quantity;
  }
  std::cout << '\n';
}
