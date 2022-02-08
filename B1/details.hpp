#ifndef B1_DETAILS_HPP
#define B1_DETAILS_HPP

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cstdlib>

namespace details
{
  template<typename T>
  std::function<bool(const T &, const T &)> getComparator(const char *order)
  {
    if (order == nullptr)
    {
      throw std::invalid_argument("Order can't be nullptr");
    }
    if (std::strcmp(order, "descending") == 0)
    {
      return std::greater<T>();
    }
    else if (std::strcmp(order, "ascending") == 0)
    {
      return std::less<T>();
    }
    else
    {
      throw std::invalid_argument("Invalid order of sort");
    }
  }

  template<template<typename> class Policy, typename Container>
  void sort(Container &container,
      std::function<bool(const typename Container::value_type &, const typename Container::value_type &)> compare)
  {
    if (compare == nullptr)
    {
      throw std::invalid_argument("Compare function pointer was nullptr");
    }
    using iterator_t = typename Policy<Container>::iterator_t;
    for (iterator_t i = Policy<Container>::begin(container); i != Policy<Container>::end(container); ++i)
    {
      for (iterator_t j = i; j != Policy<Container>::end(container); ++j)
      {
        if (!compare(Policy<Container>::getElement(container, i), Policy<Container>::getElement(container, j)))
        {
          std::swap(Policy<Container>::getElement(container, i), Policy<Container>::getElement(container, j));
        }
      }
    }
  }

  template<typename Container>
  void print(const Container &container, const char *separator = " ")
  {
    if (!separator)
    {
      throw std::invalid_argument("Separator is nullptr");
    }
    for (typename Container::const_iterator i = container.begin(); i != container.end(); ++i)
    {
      if (i != container.begin())
      {
        std::cout << separator;
      }
      std::cout << *i;
    }
  }
}

#endif
