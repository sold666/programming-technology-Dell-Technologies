#include <sstream>
#include <boost/test/unit_test.hpp>
#include "data-structure.hpp"

BOOST_AUTO_TEST_SUITE(test_data_structure)

struct Fixture
{
  const char SEPARATOR = ',';

  DataStruct dataStruct;
  std::istringstream input;
};

BOOST_FIXTURE_TEST_CASE(ValidKeys, Fixture)
{
  input.str("1, 2, something");
  input >> dataStruct;
  BOOST_CHECK_EQUAL(dataStruct.key1, 1);
  BOOST_CHECK_EQUAL(dataStruct.key2, 2);
  std::ostringstream out;
  out << dataStruct;
  BOOST_CHECK_EQUAL(out.str(), "1,2,something");
}

BOOST_FIXTURE_TEST_CASE(ValidString, Fixture)
{
  input.str("1, 3, something");
  input >> dataStruct;
  BOOST_CHECK_EQUAL(dataStruct.str, "something");
  std::ostringstream out;
  out << dataStruct;
  BOOST_CHECK_EQUAL(out.str(), "1,3,something");
}

BOOST_FIXTURE_TEST_CASE(InvalidKeys, Fixture)
{
  input.str("10, 1, something");
  input >> dataStruct;
  BOOST_CHECK(input.fail());
  input.clear();

  input.str("1, -20, something");
  input >> dataStruct;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(InvalidSeparator, Fixture)
{
  input.str("1/ 3/ something");
  input >> dataStruct;
  BOOST_CHECK(input.fail());
}

BOOST_FIXTURE_TEST_CASE(InvalidString, Fixture)
{
  input.str("1, 3,");
  input >> dataStruct;
  BOOST_CHECK(input.fail());
}

BOOST_AUTO_TEST_SUITE_END()
