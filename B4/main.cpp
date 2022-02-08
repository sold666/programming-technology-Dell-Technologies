#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data-structure.hpp"

int main()
{
  std::vector<DataStruct> vector ((std::istream_iterator<DataStruct>(std::cin)),
      std::istream_iterator<DataStruct>());
  if (!std::cin.eof())
  {
    std::cerr << "Invalid input.";
    return 2;
  }
  std::sort(vector.begin(), vector.end(), DataStructComparator());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
