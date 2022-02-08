#include <iostream>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include "parser.hpp"
#include "phonebook-interface.hpp"
#include "factorial-container.hpp"

void taskOne()
{
  PhoneBookUI phoneBook;
  std::for_each(std::istream_iterator<Command>(std::cin), std::istream_iterator<Command>(),
      [&phoneBook](const Command& command)
      {
      command(&phoneBook, std::cout);
      });
}

void taskTwo()
{
  const size_t factorial = 10;
  FactorialContainer container(factorial);
  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
  std::copy(container.rbegin(), container.rend(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
