#include "tasks.hpp"
#include <vector>
#include <forward_list>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <cstdlib>
#include "policies.hpp"
#include "details.hpp"

void taskOne(const char* order)
{
  std::function<bool(const int&, const int&)> comparator = details::getComparator<int>(order);
  std::vector<int> vector;
  int numbers = 0;
  while (std::cin >> numbers)
  {
    vector.push_back(numbers);
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Error reading numbers from a stream");
  }
  if (vector.empty())
  {
    return;
  }
  std::vector<int> vectorAt = vector;
  std::forward_list<int> list(vector.begin(), vector.end());

  details::sort<IndexPolicy>(vector, comparator);
  details::sort<AtPolicy>(vectorAt, comparator);
  details::sort<IteratorPolicy>(list, comparator);
  details::print(vector);
  std::cout << '\n';
  details::print(vectorAt);
  std::cout << '\n';
  details::print(list);
  std::cout << '\n';
}

void taskTwo(const char *filename)
{
  if (filename == nullptr)
  {
    throw std::invalid_argument("File name can't be empty");
  }
  std::ifstream file(filename);
  if (!file)
  {
    throw std::runtime_error("Can't open the file");
  }
  size_t size = 150;
  size_t amountFileContent = 0;
  const double GOLDEN_RATIO_FACTOR = 1.61;
  std::unique_ptr<char[], decltype(&std::free)> array(static_cast<char*>(std::malloc(size)), std::free);
  if (!array)
  {
    throw std::bad_alloc();
  }
  while(file)
  {
    file.read(array.get() + amountFileContent, size - amountFileContent);
    amountFileContent += file.gcount();

    if (size == amountFileContent)
    {
      size = static_cast<size_t>(size * GOLDEN_RATIO_FACTOR);
      std::unique_ptr<char[], decltype(&std::free)> tempArray (static_cast<char*>(std::realloc(array.get(), size)), std::free);
      if (!tempArray)
      {
        throw std::bad_alloc();
      }
      array.release();
      array = std::move(tempArray);
    }
  }
  if (!file.eof())
  {
    throw std::runtime_error("Read error");
  }
  if (amountFileContent)
  {
    std::vector<char> vector(array.get(), array.get() + amountFileContent);
    details::print(vector, "");
  }
}

void taskThree()
{
  std::vector<int> vector;
  int number = 0;
  while (std::cin >> number)
  {
    if (number == 0)
    {
      break;
    }
    vector.push_back(number);
  }
  if (number != 0)
  {
    throw std::runtime_error("Last number must be 0");
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Incorrect input");
  }
  if (vector.empty())
  {
    return;
  }
  if (vector.back() == 1)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      if (*(i) % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        ++i;
      }
    }
  }
  else if (vector.back() == 2)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      if (*(i) % 3 == 0)
      {
        const int value = 1;
        i = vector.insert(++i, 3, value) + 3;
      }
      else
      {
        ++i;
      }
    }
  }
  details::print(vector, " ");
  std::cout << '\n';
}

void taskFour(const char *order, int size)
{
  if (size < 1)
  {
    throw std::invalid_argument("Wrong size");
  }
  std::vector<double> vector(size);
  std::function<bool(const double, const double)> compare = details::getComparator<double>(order);
  fillRandom(vector.data(), size);
  details::print(vector, " ");
  std::cout << '\n';
  details::sort<IndexPolicy>(vector, compare);
  details::print(vector, " ");
  std::cout << '\n';
}

void fillRandom(double * array, int size)
{
  if (!array)
  {
    throw std::invalid_argument("Array is empty");
  }
  if (size < 1)
  {
    throw std::invalid_argument("Wrong size");
  }
  for (int i = 0; i < size; i++)
  {
    array[i] = -1 + static_cast<double>(std::rand()) / RAND_MAX * 2;
  }
}
