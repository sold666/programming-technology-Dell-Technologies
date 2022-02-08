#include <iostream>
#include <sstream>
#include <stdexcept>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  if ((argc != 2))
  {
    std::cerr << "Invalid count of arguments";
    return 1;
  }
  size_t taskNum = 0;
  std::istringstream stream(argv[1]);
  stream >> taskNum;
  if (!stream.eof())
  {
    std::cerr << "Error when reading argument from a stream";
    return 1;
  }
  if ((taskNum < 1) || (taskNum > 2))
  {
    std::cerr << "Invalid number of task";
    return 1;
  }
  if (taskNum == 1)
  {
    try
    {
      taskOne();
    }
    catch (std::runtime_error &error)
    {
      std::cerr << error.what();
      return 2;
    }
    catch (std::invalid_argument &error)
    {
      std::cerr << error.what();
      return 1;
    }
  }
  if (taskNum == 2)
  {
    try
    {
      taskTwo();
    }
    catch (const std::overflow_error& error)
    {
      std::cerr << error.what() << '\n';
      return 2;
    }
    catch (const std::out_of_range& error)
    {
      std::cerr << error.what() << '\n';
      return 2;
    }
  }
  return 0;
}
