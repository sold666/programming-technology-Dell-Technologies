#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstddef>
#include <ctime>
#include <random>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  if ((argc < 2) || (argc > 4))
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

  if ((taskNum < 1) || (taskNum > 4))
  {
    std::cerr << "Invalid number of task";
    return 1;
  }
  if (taskNum == 1)
  {
    if (argc != 3)
    {
      std::cerr << "Invalid count of arguments";
      return 1;
    }
    try
    {
      taskOne(argv[2]);
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
    if (argc != 3)
    {
      std::cerr << "Invalid count of arguments";
      return 1;
    }
    try
    {
      taskTwo(argv[2]);
    }
    catch (std::invalid_argument &error)
    {
      std::cerr << error.what();
      return 1;
    }
    catch (std::runtime_error &error)
    {
      std::cerr << error.what();
      return 2;
    }
    catch(std::bad_alloc &error)
    {
      std::cerr << error.what();
      return 2;
    }
  }
  if (taskNum == 3)
  {
    if (argc != 2)
    {
      std::cerr << "Invalid count of arguments";
      return 1;
    }
    try
    {
      taskThree();
    }
    catch (std::runtime_error& error)
    {
      std::cerr << error.what();
      return 2;
    }
  }
  if (taskNum == 4)
  {
    if (argc != 4)
    {
      std::cerr << "Invalid count of arguments";
      return 1;
    }
    try
    {
      std::stringstream stream_size(argv[3]);
      int size = 0;
      stream_size >> size;
      if (!stream_size.eof())
      {
        std::cerr << "Error while reading size";
        return 1;
      }
      std::srand(static_cast<double>(std::time(nullptr)));
      taskFour(argv[2], size);
    }
    catch (std::invalid_argument& error)
    {
      std::cerr << error.what();
      return 1;
    }
  }
  return 0;
}
