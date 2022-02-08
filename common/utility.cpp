#include "utility.hpp"
#include <iostream>
#include <cctype>

std::istream& skipWS(std::istream& input)
{
  while (isblank(input.peek()))
  {
    input.get();
  }
  return input;
}
