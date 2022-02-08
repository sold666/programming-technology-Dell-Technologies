#ifndef B3_FACTORIAL_CONTAINER_HPP
#define B3_FACTORIAL_CONTAINER_HPP

#include <iterator>
#include <cstddef>

class FactorialContainer
{
public:
  class const_iterator : public std::iterator<std::bidirectional_iterator_tag, size_t, std::ptrdiff_t, size_t, size_t>
  {
  public:
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    reference operator*() const;
    bool operator!=(const const_iterator& otherIterator) const;
    bool operator==(const const_iterator& otherIterator) const;

  private:
    size_t number_;
    size_t factorial_;
    size_t maxNumber_;
    friend FactorialContainer;
    const_iterator(size_t factorial, size_t number, size_t maxNumber);
  };

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  explicit FactorialContainer(size_t size = 0);
  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t maxNumber_;
  size_t maxFactorial_;
};

#endif
