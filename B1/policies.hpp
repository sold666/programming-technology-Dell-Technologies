#ifndef B1_POLICIES_HPP
#define B1_POLICIES_HPP

#include <cstddef>
#include <stdexcept>

template <class Container>
struct IteratorPolicy
{
  using iterator_t = typename Container::iterator;
  using value_type = typename Container::value_type;
  static iterator_t begin(Container& collection)
  {
    return collection.begin();
  }
  static value_type& getElement(Container&, iterator_t index)
  {
    return *index;
  }
  static iterator_t end(Container& collection)
  {
    return collection.end();
  }
};

template <class Container>
struct IndexPolicy
{
  using iterator_t = size_t;
  using value_type = typename Container::value_type;
  static iterator_t begin(Container&)
  {
    return 0;
  }
  static value_type& getElement(Container& collection, iterator_t index)
  {
    if (index >= collection.size())
    {
      throw std::out_of_range("Out of vector bounds");
    }
    return collection[index];
  }
  static iterator_t end(Container& collection)
  {
    return collection.size();
  }
};

template <class Container>
struct AtPolicy
{
  using iterator_t = size_t;
  using value_type = typename Container::value_type;
  static iterator_t begin(Container&)
  {
    return 0;
  }
  static value_type& getElement(Container& collection, iterator_t index)
  {
    return collection.at(index);
  }
  static iterator_t end(Container& collection)
  {
    return collection.size();
  }
};

#endif
