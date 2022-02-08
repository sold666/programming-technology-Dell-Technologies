#include <stdexcept>
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(task3)

struct Fixture
{
  const std::string INPUT_NUMBERS_ONE = "1 4 2 2 5 7 8 1 0\n";
  const std::string RIGHT_OUTPUT_NUMBERS_ONE = "1 5 7 1\n";

  const std::string INPUT_NUMBERS_TWO = "1 4 3 3 5 7 8 2 0\n";
  const std::string RIGHT_OUTPUT_NUMBERS_TWO = "1 4 3 1 1 1 3 1 1 1 5 7 8 2\n";

  const std::string INPUT_NUMBERS_THREE = "1 4 3 3 5 7 8 0\n";
  const std::string RIGHT_OUTPUT_NUMBERS_THREE = "1 4 3 3 5 7 8\n";

  const std::string INVALID_INPUT_ONE = "2.3 1.1 3.4 5.6 4.9 7.9 10.0 -1.2\n";
  const std::string INVALID_INPUT_TWO = "1 4 ds 2 5 plz 8 -1\n";

  const std::string EMPTY_INPUT = "";
  const std::string RIGHT_EMPTY_OUTPUT = "";

  Fixture():
    backupCin(std::cin.rdbuf(inputStream.rdbuf())),
    backupCout(std::cout.rdbuf(outputStream.rdbuf()))
  {}

  ~Fixture()
  {
    std::cin.rdbuf(backupCin);
    std::cout.rdbuf(backupCout);
  }

  std::streambuf* backupCin;
  std::streambuf* backupCout;
  std::istringstream inputStream;
  std::ostringstream outputStream;
};

BOOST_FIXTURE_TEST_CASE(ValidateSubtask1, Fixture)
{
  inputStream.str(INPUT_NUMBERS_ONE);
  taskThree();
  const std::string outputNumbers = outputStream.str();
  BOOST_CHECK_EQUAL(outputNumbers, RIGHT_OUTPUT_NUMBERS_ONE);
}

BOOST_FIXTURE_TEST_CASE(ValidateSubtask2, Fixture)
{
  inputStream.str(INPUT_NUMBERS_TWO);
  taskThree();
  const std::string outputNumbers = outputStream.str();
  BOOST_CHECK_EQUAL(outputNumbers, RIGHT_OUTPUT_NUMBERS_TWO);
}

BOOST_FIXTURE_TEST_CASE(ValidateWhithoutSubtask, Fixture)
{
  inputStream.str(INPUT_NUMBERS_THREE);
  taskThree();
  const std::string outputNumbers = outputStream.str();
  BOOST_CHECK_EQUAL(outputNumbers, RIGHT_OUTPUT_NUMBERS_THREE);
}

BOOST_FIXTURE_TEST_CASE(ValidateExceptionWithInvalidDataTypeOne, Fixture)
{
  inputStream.str(INVALID_INPUT_ONE);
  std::cout.rdbuf(backupCout);
  BOOST_CHECK_THROW(taskThree(), std::runtime_error);
}

BOOST_FIXTURE_TEST_CASE(ValidateExceptionWithInvalidDataTypeTwo, Fixture)
{
  inputStream.str(INVALID_INPUT_TWO);
  std::cout.rdbuf(backupCout);
  BOOST_CHECK_THROW(taskThree(), std::runtime_error);
}

BOOST_FIXTURE_TEST_CASE(ValidateEmptyInput, Fixture)
{
  inputStream.str(EMPTY_INPUT);
  taskThree();
  const std::string output = outputStream.str();
  BOOST_CHECK_EQUAL(output, RIGHT_EMPTY_OUTPUT);
}

BOOST_AUTO_TEST_SUITE_END()
