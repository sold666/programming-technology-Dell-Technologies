#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <forward_list>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"
#include "details.hpp"
#include "policies.hpp"

BOOST_AUTO_TEST_SUITE(task1)

struct Fixture
{
  const std::string EMPTY_INPUT = "";
  const std::string INPUT_NUMBERS = "1 4 2 2 5 7 8 -1\n";
  const std::string RIGHT_OUTPUT_NUMBERS_ASCENDING = "-1 1 2 2 4 5 7 8\n-1 1 2 2 4 5 7 8\n-1 1 2 2 4 5 7 8\n";
  const std::string RIGHT_OUTPUT_NUMBERS_DESCENDING = "8 7 5 4 2 2 1 -1\n8 7 5 4 2 2 1 -1\n8 7 5 4 2 2 1 -1\n";
  const std::string RIGHT_EMPTY_OUTPUT = "";
  const std::string INVALID_INPUT_ONE = "2.0 1.2 3.5 5.6 4.1 7.8 9.9 -1.0\n";
  const std::string INVALID_INPUT_TWO = "1 4 ds 2 5 plz 8 -1\n";
  const std::string INVALID_INPUT_THREE = "i love programming\n";

  Fixture():
    backupCin(std::cin.rdbuf(inputStream.rdbuf())),
    backupCout(std::cout.rdbuf(outputStream.rdbuf()))
  {}

  ~Fixture()
  {
    std::cin.rdbuf(backupCin);
    std::cout.rdbuf(backupCout);
  };

  std::streambuf* backupCin;
  std::streambuf* backupCout;
  std::istringstream inputStream;
  std::ostringstream outputStream;
};

struct FixtureForSort
{
  FixtureForSort():
    vector({3, -2, 1, 1, 6, 99}),
    vectorAscending({-2, 1, 1, 3, 6, 99}),
    vectorDescending({99, 6, 3, 1, 1, -2}),
    list(vector.begin(), vector.end()),
    listAscending(vectorAscending.begin(), vectorAscending.end()),
    listDescending(vectorDescending.begin(), vectorDescending.end())
  {}

  std::vector<int> vector;
  std::vector<int> vectorAscending;
  std::vector<int> vectorDescending;
  std::forward_list<int> list;
  std::forward_list<int> listAscending;
  std::forward_list<int> listDescending;
};

BOOST_FIXTURE_TEST_CASE(ValidateGetComparator, FixtureForSort)
{
  BOOST_CHECK_THROW(details::getComparator<int>(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(details::getComparator<int>("fail"), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(ValidateSortingFunctionWithIndex, FixtureForSort)
{
  details::sort<IndexPolicy>(vector, details::getComparator<int>("ascending"));
  for (size_t i = 0; i < vector.size(); i++)
  {
    BOOST_CHECK_EQUAL(vector[i], vectorAscending[i]);
  }
  details::sort<IndexPolicy>(vector, details::getComparator<int>("descending"));
  for (size_t i = 0; i < vector.size(); i++)
  {
    BOOST_CHECK_EQUAL(vector[i], vectorDescending[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(ValidateSortingFunctionWithAt, FixtureForSort)
{
  details::sort<AtPolicy>(vector, details::getComparator<int>("ascending"));
  for (size_t i = 0; i < vector.size(); i++)
  {
    BOOST_CHECK_EQUAL(vector[i], vectorAscending[i]);
  }
  details::sort<AtPolicy>(vector, details::getComparator<int>("descending"));
  for (size_t i = 0; i < vector.size(); i++)
  {
    BOOST_CHECK_EQUAL(vector[i], vectorDescending[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(ValidateSortingFunctionWithIterator, FixtureForSort)
{
  details::sort<IteratorPolicy>(list, details::getComparator<int>("ascending"));
  BOOST_CHECK(list == listAscending);
  details::sort<IteratorPolicy>(list, details::getComparator<int>("descending"));
  BOOST_CHECK(list == listDescending);
}

BOOST_FIXTURE_TEST_CASE(ValidateInputAscendingOrder, Fixture)
{
  inputStream.str(INPUT_NUMBERS);
  taskOne("ascending");
  const std::string outputNumbers = outputStream.str();
  BOOST_CHECK_EQUAL(outputNumbers, RIGHT_OUTPUT_NUMBERS_ASCENDING);
}

BOOST_FIXTURE_TEST_CASE(ValidateInputDescendingOrder, Fixture)
{
  inputStream.str(INPUT_NUMBERS);
  taskOne("descending");
  const std::string outputNumbers = outputStream.str();
  BOOST_CHECK_EQUAL(outputNumbers, RIGHT_OUTPUT_NUMBERS_DESCENDING);
}

BOOST_FIXTURE_TEST_CASE(ValidateWhithEmptyInput, Fixture)
{
  inputStream.str(EMPTY_INPUT);
  taskOne("ascending");
  const std::string output = outputStream.str();
  BOOST_CHECK_EQUAL(output, RIGHT_EMPTY_OUTPUT);
}

BOOST_FIXTURE_TEST_CASE(ValidateExceptionWithInvalidDataTypeAscending, Fixture)
{
  inputStream.str(INVALID_INPUT_ONE);
  BOOST_CHECK_THROW(taskOne("ascending"), std::runtime_error);
  inputStream.str(INVALID_INPUT_TWO);
  BOOST_CHECK_THROW(taskOne("ascending"), std::runtime_error);
  inputStream.str(INVALID_INPUT_THREE);
  BOOST_CHECK_THROW(taskOne("ascending"), std::runtime_error);
}

BOOST_FIXTURE_TEST_CASE(ValidateExceptionWithInvalidDataTypeDescending, Fixture)
{
  inputStream.str(INVALID_INPUT_ONE);
  BOOST_CHECK_THROW(taskOne("descending"), std::runtime_error);
  inputStream.str(INVALID_INPUT_TWO);
  BOOST_CHECK_THROW(taskOne("descending"), std::runtime_error);
  inputStream.str(INVALID_INPUT_THREE);
  BOOST_CHECK_THROW(taskOne("descending"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(InvalidOrder)
{
  BOOST_CHECK_THROW(taskOne(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(taskOne("Wrong order"), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
