#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(task4)

const size_t VECTOR_SIZE = 5;

struct Fixture
{

  Fixture() :
    backupCout(std::cout.rdbuf(stream.rdbuf()))
  {}

  ~Fixture()
  {
    std::cout.rdbuf(backupCout);
  }

  std::streambuf *backupCout;
  std::stringstream stream;
};

BOOST_AUTO_TEST_CASE(ValidateTask)
{
  std::vector<double> vector(VECTOR_SIZE);
  fillRandom(vector.data(), VECTOR_SIZE);

  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    BOOST_CHECK((vector[i] < 1.0) && (vector[i] > -1.0));
  }
}

BOOST_AUTO_TEST_CASE(ValidateFunctionRandomFilling)
{
  std::vector<double> vector(VECTOR_SIZE);
  fillRandom(vector.data(), VECTOR_SIZE);
  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    BOOST_CHECK((vector[i] < 1.0) && (vector[i] > -1.0));
  }
}

BOOST_FIXTURE_TEST_CASE(ValidateOrderAscending, Fixture)
{
  taskFour("ascending", VECTOR_SIZE);
  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    double temp;
    stream >> temp;
    BOOST_CHECK((temp < 1.0) && (temp > -1.0));
  }
  std::vector<double> vectorOut;
  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    double temp;
    stream >> temp;
    vectorOut.push_back(temp);
  }
  BOOST_CHECK(std::is_sorted(vectorOut.begin(), vectorOut.end(), std::less<>()));
}

BOOST_FIXTURE_TEST_CASE(ValidateOrderDescending, Fixture)
{
  taskFour("descending", VECTOR_SIZE);
  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    double temp;
    stream >> temp;
    BOOST_CHECK((temp < 1.0) && (temp > -1.0));
  }
  std::vector<double> vectorOut;
  for (size_t i = 0; i < VECTOR_SIZE; ++i)
  {
    double temp;
    stream >> temp;
    vectorOut.push_back(temp);
  }
  BOOST_CHECK(std::is_sorted(vectorOut.begin(), vectorOut.end(), std::greater<>()));
}

BOOST_AUTO_TEST_CASE(InvalidArguments)
{
  BOOST_CHECK_THROW(taskFour("ascending", 0), std::invalid_argument);
  BOOST_CHECK_THROW(taskFour("descending", -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(InvalidOrder)
{
  BOOST_CHECK_THROW(taskFour("fail", 5), std::invalid_argument);
  BOOST_CHECK_THROW(taskFour("not order", 5), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
