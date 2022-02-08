#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(task2)

struct Fixture
{
  const std::string FILE_NAME = "text.txt";
  const std::string DATA_IN_FILE = "Something of the file";
  const std::string DATA = "1 4 2 2 5 7 8 -1\n";

  Fixture():
    backupCout(std::cout.rdbuf(outputStream.rdbuf()))
  {
    outputFileStream.open(FILE_NAME);
    outputFileStream << DATA_IN_FILE;
    outputFileStream.close();
  }

  ~Fixture()
  {
    std::cout.rdbuf(backupCout);
  };

  std::streambuf* backupCout;
  std::ofstream outputFileStream;
  std::ostringstream outputStream;
};

BOOST_FIXTURE_TEST_CASE(ValidateWorkTaskTwo, Fixture)
{
  outputFileStream.open(FILE_NAME);
  outputFileStream << DATA;
  outputFileStream.close();
  taskTwo("text.txt");
  const std::string output = outputStream.str();
  BOOST_CHECK_EQUAL(output, DATA);
  std::remove("text.txt");
}

BOOST_AUTO_TEST_CASE(InvalidFilesName)
{
  const char *nameFile = "Fail name";
  BOOST_CHECK_THROW(taskTwo(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(taskTwo(nameFile), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
