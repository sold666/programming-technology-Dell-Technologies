#include <vector>
#include <forward_list>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "policies.hpp"

BOOST_AUTO_TEST_SUITE(policies)

struct Fixture
{
  const size_t VECTOR_SIZE = 7;

  Fixture() :
    vector({10, 32, 99, 1, 7, 88, 1}),
    list({18, 52, 99, 3, 7, 78, 3})
  {}

  std::vector<int> vector;
  std::forward_list<int> list;
};

BOOST_FIXTURE_TEST_CASE(ValidateAtPolicy, Fixture)
{
  BOOST_CHECK_EQUAL(VECTOR_SIZE, AtPolicy<std::vector<int>>::end(vector));
  BOOST_CHECK_EQUAL(0, AtPolicy<std::vector<int>>::begin(vector));
  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    BOOST_CHECK_EQUAL(vector.at(i), AtPolicy<std::vector<int>>::getElement(vector, i));
  }
}

BOOST_FIXTURE_TEST_CASE(InvalidAtPolicy, Fixture)
{
  BOOST_CHECK_THROW(AtPolicy<std::vector<int>>::getElement(vector, 15), std::out_of_range);
  BOOST_CHECK_THROW(AtPolicy<std::vector<int>>::getElement(vector, -1), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(ValidateBracketsWithIndex, Fixture)
{
  BOOST_CHECK_EQUAL(VECTOR_SIZE, IndexPolicy<std::vector<int>>::end(vector));
  BOOST_CHECK_EQUAL(0, IndexPolicy<std::vector<int>>::begin(vector));
  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    BOOST_CHECK_EQUAL(vector.at(i), IndexPolicy<std::vector<int>>::getElement(vector, i));
  }
}

BOOST_FIXTURE_TEST_CASE(InvalidBracketsWithIndex, Fixture)
{
  BOOST_CHECK_THROW(IndexPolicy<std::vector<int>>::getElement(vector, 15), std::out_of_range);
  BOOST_CHECK_THROW(IndexPolicy<std::vector<int>>::getElement(vector, -1), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(ValidateIterator, Fixture)
{
  auto i = ++list.begin();
  BOOST_CHECK(*i == IteratorPolicy<std::forward_list<int>>::getElement(list, i));
  BOOST_CHECK(list.begin() == IteratorPolicy<std::forward_list<int>>::begin(list));
  BOOST_CHECK(list.end() == IteratorPolicy<std::forward_list<int>>::end(list));
}

BOOST_AUTO_TEST_SUITE_END()
