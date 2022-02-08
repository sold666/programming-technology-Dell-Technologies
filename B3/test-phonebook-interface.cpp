#include <ostream>
#include <boost/test/unit_test.hpp>
#include "phonebook-interface.hpp"

BOOST_AUTO_TEST_SUITE(test_phonebook_interface)

struct Fixture
{
  PhoneBookUI phonebook;
  const PhoneBook::note_t note1 = {"89475985455", "andrew"};
  const PhoneBook::note_t note2 = {"89129023002", "alla"};
  const PhoneBook::note_t note3 = {"89212331234", "aeqwe\"max\"erreetre"};
  const PhoneBook::note_t note4 = {"89473956232", "asadd\"s;as;d'd"};
  const PhoneBook::note_t note5 = {"89112323455", "msaasdlsals d"};
  const PhoneBook::note_t note6 = {"89122439552", "dsdkdskds"};

  Fixture()
  {
    phonebook.add(note1, output);
    phonebook.add(note2, output);
    phonebook.add(note3, output);
  }

  std::ostringstream output;
  std::ostringstream outputSecond;
};

BOOST_FIXTURE_TEST_CASE(ValidateStore, Fixture)
{
  const std::string newMarkName = "new-mark";
  phonebook.store("current", newMarkName, output);
  BOOST_CHECK_EQUAL(output.str(), "");

  phonebook.show(newMarkName, output);
  const std::string expected = note1.number + ' ' + note1.name + '\n';
  BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(ValidateInsert, Fixture)
{
  phonebook.insert(PhoneBook::AFTER, "current", note2, output);
  BOOST_CHECK_EQUAL(output.str(), "");
  PhoneBookUI::steps_t steps;
  steps.num = -1;
  steps.flag = PhoneBookUI::steps_t::NUMERIC;
  phonebook.move(steps, "current", output);
  BOOST_CHECK_EQUAL(output.str(), "");
  phonebook.show("current", output);
  const std::string expected = note1.number + ' ' + note1.name + '\n';
  BOOST_CHECK_EQUAL(output.str(), expected);

  phonebook.insert(PhoneBook::AFTER, "current", note2, outputSecond);
  BOOST_CHECK_EQUAL(outputSecond.str(), "");
  steps.num = 1;
  phonebook.move(steps, "current", outputSecond);
  BOOST_CHECK_EQUAL(outputSecond.str(), "");
  phonebook.show("current", outputSecond);
  const std::string expectedTwo = note2.number + ' ' + note2.name + '\n';
  BOOST_CHECK_EQUAL(outputSecond.str(), expectedTwo);
}

BOOST_FIXTURE_TEST_CASE(ValidateMove, Fixture)
{
  PhoneBookUI::steps_t steps;
  steps.steps = PhoneBookUI::steps_t::FIRST;
  phonebook.move(steps, "current", output);
  BOOST_CHECK_EQUAL(output.str(), "");
  phonebook.show("current", output);
  std::string expected = note1.number + ' ' + note1.name + '\n';
  BOOST_CHECK_EQUAL(output.str(), expected);

  steps.steps = PhoneBookUI::steps_t::LAST;
  phonebook.move(steps, "current", outputSecond);
  BOOST_CHECK_EQUAL(outputSecond.str(), "");
  phonebook.show("current", outputSecond);
  expected = note3.number + ' ' + note3.name + '\n';
  BOOST_CHECK_EQUAL(outputSecond.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(ValidateMoveNum, Fixture)
{
  phonebook.add(note4, output);
  phonebook.add(note5, output);
  phonebook.add(note6, output);
  PhoneBookUI::steps_t steps;
  steps.num = 3;
  steps.flag = PhoneBookUI::steps_t::NUMERIC;
  phonebook.move(steps, "current", output);
  BOOST_CHECK_EQUAL(output.str(), "");
  phonebook.show("current", output);
  std::string expected = note4.number + ' ' + note4.name + '\n';
  BOOST_CHECK_EQUAL(output.str(), expected);

  steps.num = -3;
  phonebook.move(steps, "current", outputSecond);
  BOOST_CHECK_EQUAL(outputSecond.str(), "");
  phonebook.show("current", outputSecond);
  expected = note1.number + ' ' + note1.name + '\n';
  BOOST_CHECK_EQUAL(outputSecond.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(ValidateDelete, Fixture)
{
  phonebook.deleteMark("current", output);
  BOOST_CHECK_EQUAL(output.str(), "");
  phonebook.show("current", output);
  std::string expected = note2.number + ' ' + note2.name + '\n';
  BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_SUITE_END()
