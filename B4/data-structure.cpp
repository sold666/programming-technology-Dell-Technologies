#include "data-structure.hpp"
#include <sstream>
#include <cctype>
#include <boost/io/ios_state.hpp>
#include "utility.hpp"

std::istream& operator>>(std::istream& input, DataStruct& dataStruct)
{
  boost::io::ios_flags_saver saver(input);
  std::istream::sentry stream(input);
  if (!stream)
  {
    return input;
  }
  const char SEPARATOR = ',';
  const int LOWER_LIM = -5;
  const int UPPER_LIM= 5;
  int key_one;
  std::string str;
  input >> std::noskipws >> std::ws >> key_one;
  if (!input || (key_one < LOWER_LIM) || (key_one > UPPER_LIM))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  char symbol;
  input >> symbol;
  if (!input || symbol != SEPARATOR)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  int key_two;
  input >> skipWS >> key_two;
  if (!input || (key_two < LOWER_LIM) || (key_two > UPPER_LIM))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  input >> symbol;
  if (!input || symbol != SEPARATOR)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  input >> skipWS;
  std::getline(input, str);
  if (!input || str.empty())
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  dataStruct = {key_one, key_two, str};
  return input;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  const char SEPARATOR = ',';
  std::ostream::sentry stream(out);
  if (!stream)
  {
    return out;
  }
  out << dataStruct.key1 << SEPARATOR << dataStruct.key2 << SEPARATOR << dataStruct.str;
  return out;
}

bool DataStructComparator::operator()(const DataStruct& dataOne, const DataStruct& dataTwo) const
{
  if (dataOne.key1 != dataTwo.key1)
  {
    return dataOne.key1 < dataTwo.key1;
  }
  if (dataOne.key2 != dataTwo.key2)
  {
    return dataOne.key2 < dataTwo.key2;
  }
  return dataOne.str.length() < dataTwo.str.length();
}
