#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "factorial-container.hpp"
#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(factorial_container)

BOOST_AUTO_TEST_CASE(ValidateReverseAndSimpleIterator)
{
  const size_t factorialNumber = 10;
  FactorialContainer container(factorialNumber);
  FactorialContainer::const_iterator iterator(container.begin());
  BOOST_CHECK_THROW(--iterator, std::out_of_range);
  BOOST_CHECK_THROW(iterator--, std::out_of_range);
  size_t factorial = 1;
  for (size_t i = 1; i != factorialNumber + 1 && iterator != container.end(); ++i, ++iterator)
  {
    factorial *= i;
    BOOST_CHECK(*(iterator) == factorial);
  }
  BOOST_CHECK_THROW(++iterator, std::out_of_range);
  BOOST_CHECK_THROW(iterator++, std::out_of_range);

  FactorialContainer::const_reverse_iterator reverseIterator(container.rbegin());
  BOOST_CHECK_THROW(--reverseIterator, std::out_of_range);
  BOOST_CHECK_THROW(reverseIterator--, std::out_of_range);
  for (size_t i = 10; i != 0 && reverseIterator != container.rend(); --i, ++reverseIterator)
  {
    BOOST_CHECK(*(reverseIterator) == factorial);
    factorial /= i;
  }
  BOOST_CHECK_THROW(++reverseIterator, std::out_of_range);
  BOOST_CHECK_THROW(reverseIterator++, std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ValidateComparisonOperators)
{
  const size_t factorialNumber = 10;
  FactorialContainer container(factorialNumber);
  FactorialContainer::const_iterator it1 = container.begin();
  FactorialContainer::const_iterator it2 = container.end();
  BOOST_CHECK(it1 != it2);
  FactorialContainer::const_iterator it3 = container.end();
  BOOST_CHECK(it3 == it2);
}

BOOST_AUTO_TEST_CASE(CheckContainerExceptions)
{
  FactorialContainer emptyContainer;
  BOOST_CHECK_THROW(++emptyContainer.begin(), std::out_of_range);
  BOOST_CHECK_THROW(emptyContainer.begin()++, std::out_of_range);
  BOOST_CHECK_THROW(--emptyContainer.rbegin(), std::out_of_range);
  BOOST_CHECK_THROW(emptyContainer.rbegin()--, std::out_of_range);
  BOOST_CHECK(emptyContainer.begin() == emptyContainer.end());
  BOOST_CHECK(emptyContainer.rbegin() == emptyContainer.rend());
  BOOST_CHECK_THROW(FactorialContainer container(30), std::overflow_error);
}

BOOST_AUTO_TEST_SUITE_END()
