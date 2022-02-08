#ifndef B4_DATA_STRUCTURE_HPP
#define B4_DATA_STRUCTURE_HPP

#include <iosfwd>
#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& input, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct);

struct DataStructComparator
{
  bool operator()(const DataStruct& dataOne, const DataStruct& dataTwo) const;
};

#endif
