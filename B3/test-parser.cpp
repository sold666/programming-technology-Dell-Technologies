#include <sstream>
#include <boost/test/unit_test.hpp>
#include "parser.hpp"
#include "phonebook.hpp"
#include "phonebook-interface.hpp"

BOOST_AUTO_TEST_SUITE(test_parser)

struct Fixture
{
  const std::string INVALID_NAME = "Name without quotation marks";
  const std::string INVALID_NUMBER = "89ewsdsder3245";
  const std::string NUMBER = "89243123245";
  const std::string RIGHT_NAME = "\"name\"";
  std::string invalidCommandAdd = "add1 82122 \"vlad\"";
  std::string invalidCommandStore = "store1 current new-mark";
  std::string invalidCommandInsert = "insert21 before 82122 \"vlad\"";
  std::string invalidCommandDelete = "delete1 new-mark";
  std::string invalidCommandShow = "show1 current";
  std::string invalidCommandMove = "move4 current last";
  std::string invalidPosition = "insert sbefore 221232\"sadsadff\"";

  PhoneBookUI book;
  Command command;
  std::stringstream stream;
};

BOOST_FIXTURE_TEST_CASE(CheckNameWithoutQuotationMarks, Fixture)
{
  PhoneBook::note_t note;
  stream << NUMBER << ' ' << INVALID_NAME;
  stream >> note;
  BOOST_CHECK(stream.fail());
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidNumber, Fixture)
{
  PhoneBook::note_t note;
  stream << INVALID_NUMBER << ' ' << RIGHT_NAME;
  stream >> note;
  BOOST_CHECK(stream.fail());
}

BOOST_FIXTURE_TEST_CASE(ValidateNote, Fixture)
{
  PhoneBook::note_t note;
  stream << NUMBER << ' ' << RIGHT_NAME;
  stream >> note;
  BOOST_CHECK(!stream.fail());
  BOOST_CHECK_EQUAL(note.name, "name");
  BOOST_CHECK_EQUAL(note.number, "89243123245");
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidPosition, Fixture)
{
  std::istringstream input(invalidPosition);
  input >> command;
  command(&book, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidNumberStep, Fixture)
{
  const std::string invalidSteps = "44lsa3";
  PhoneBookUI::steps_t steps;
  stream << invalidSteps;
  stream >> steps;
  BOOST_CHECK(stream.fail());
}

BOOST_FIXTURE_TEST_CASE(ValidateStringSteps, Fixture)
{
  PhoneBookUI::steps_t steps;
  std::string stepsString = "first";
  stream << stepsString;
  stream >> steps;
  BOOST_CHECK(!stream.fail());
  BOOST_CHECK(steps.steps == steps.FIRST);
  stream.clear();
  stepsString = "last";
  stream << stepsString;
  stream >> steps;
  BOOST_CHECK(!stream.fail());
  BOOST_CHECK(steps.steps == steps.LAST);
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidCommandAdd, Fixture)
{
  std::istringstream input(invalidCommandAdd);
  input >> command;
  command(&book, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidCommandStore, Fixture)
{
  std::istringstream input(invalidCommandStore);
  input >> command;
  command(&book, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidCommandInsert, Fixture)
{
  std::istringstream input(invalidCommandInsert);
  input >> command;
  command(&book, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidCommandDelete, Fixture)
{
  std::istringstream input(invalidCommandDelete);
  input >> command;
  command(&book, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidCommandShow, Fixture)
{
  std::istringstream input(invalidCommandShow);
  input >> command;
  command(&book, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(CheckInvalidCommandMove, Fixture)
{
  std::istringstream input(invalidCommandMove);
  input >> command;
  command(&book, stream);
  BOOST_CHECK_EQUAL(stream.str(), "<INVALID COMMAND>\n");
}

BOOST_AUTO_TEST_SUITE_END()
