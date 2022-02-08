#include "factorial-container.hpp"
#include <stdexcept>
#include <climits>
#include <cstddef>

FactorialContainer::const_iterator::const_iterator(size_t factorial, size_t number, size_t maxNumber):
  number_(number),
  factorial_(factorial),
  maxNumber_(maxNumber)
{}

FactorialContainer::const_iterator& FactorialContainer::const_iterator::operator++()
{
  if (number_ < maxNumber_)
  {
    ++number_;
    factorial_ *= number_;
    return *this;
  }
  throw std::out_of_range("You can't go beyond the upper bound of the factorial");
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator++(int)
{
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialContainer::const_iterator& FactorialContainer::const_iterator::operator--()
{
  if (number_ > 1)
  {
    factorial_ /= number_--;
    return *this;
  }
  throw std::out_of_range("You can't go beyond the lower bound of the factorial");
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator--(int)
{
  const_iterator temp = *this;
  --(*this);
  return temp;
}

FactorialContainer::const_iterator::reference FactorialContainer::const_iterator::operator*() const
{
  return factorial_;
}

bool FactorialContainer::const_iterator::operator!=(const const_iterator& otherIterator) const
{
  return (number_  != otherIterator.number_);
}

bool FactorialContainer::const_iterator::operator==(const const_iterator& otherIterator) const
{
  return (number_  == otherIterator.number_);
}

FactorialContainer::FactorialContainer(size_t number):
  maxNumber_(number + 1),
  maxFactorial_(1)
{
  for (size_t i = 1; i <= maxNumber_; i++)
  {
    if (maxFactorial_ > SIZE_MAX / i)
    {
      throw std::overflow_error("Factorial value exceeded the maximum possible value of its type");
    }

    maxFactorial_ *= i;
  }
}

FactorialContainer::const_iterator FactorialContainer::begin() const
{
  return const_iterator(1, 1, maxNumber_);
}

FactorialContainer::const_iterator FactorialContainer::end() const
{
  return const_iterator(maxFactorial_, maxNumber_, maxNumber_);
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return const_reverse_iterator(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return const_reverse_iterator(begin());
}
