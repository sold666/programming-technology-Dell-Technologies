#include <iterator>
#include <ostream>
#include <boost/test/unit_test.hpp>
#include "phonebook.hpp"

BOOST_AUTO_TEST_SUITE(test_phonebook)

struct Fixture
  {
  PhoneBook phonebook;
  const PhoneBook::note_t note1 = {"89243123245", "vlad"};
  const PhoneBook::note_t note2 = {"89287221242", "sasha"};
  const PhoneBook::note_t note3 = {"89242223288", "spsdop\"max\"assadsd"};
  const PhoneBook::note_t note4 = {"89243122049", "asadd\"s;as;d'd"};

  Fixture()
  {
    phonebook.addNote(note1);
    phonebook.addNote(note2);
    phonebook.addNote(note3);
  }

  std::ostringstream output;
};

BOOST_FIXTURE_TEST_CASE(ValidateRemoveMethod, Fixture)
{
  auto iterator = phonebook.begin();
  phonebook.deleteNote(iterator);
  BOOST_CHECK(iterator->name == note1.name);
  BOOST_CHECK(iterator->number == note1.number);
}

BOOST_FIXTURE_TEST_CASE(ValidateInsertAfterMethod, Fixture)
{
  auto iterator = phonebook.begin();
  phonebook.insert(note2, iterator, PhoneBook::Position::AFTER);
  BOOST_CHECK(std::next(iterator)->name == note2.name);
  BOOST_CHECK(std::next(iterator)->number == note2.number);
}

BOOST_FIXTURE_TEST_CASE(ValidateInsertBeforeMethod, Fixture)
{
  auto iterator = phonebook.begin();
  phonebook.insert(note3, iterator, PhoneBook::Position::BEFORE);
  BOOST_CHECK(phonebook.begin()->name == note3.name);
  BOOST_CHECK(phonebook.begin()->number == note3.number);
}

BOOST_FIXTURE_TEST_CASE(ValidateAdd, Fixture)
{
  phonebook.addNote(note4);
  BOOST_CHECK(std::prev(phonebook.end())->name == note4.name);
  BOOST_CHECK(std::prev(phonebook.end())->number == note4.number);
}

BOOST_AUTO_TEST_CASE(ValidateisEmpty)
{
  PhoneBook phonebookTwo;
  const PhoneBook::note_t note5 = {"89112323455", "msaasdlsals d"};
  BOOST_CHECK(phonebookTwo.isEmpty() == true);
  phonebookTwo.addNote(note5);
  BOOST_CHECK(phonebookTwo.isEmpty() == false);
}

BOOST_FIXTURE_TEST_CASE(ValidatePrint, Fixture)
{
  auto iterator = phonebook.begin();
  output << iterator;
  BOOST_CHECK_EQUAL(output.str(), iterator->number + " " + iterator->name + "\n");
}

BOOST_FIXTURE_TEST_CASE(ValidateBeginAndEnd, Fixture)
{
  BOOST_CHECK_EQUAL(phonebook.begin()->name, note1.name);
  BOOST_CHECK_EQUAL(phonebook.begin()->number, note1.number);
  BOOST_CHECK_EQUAL(std::prev(phonebook.end())->number, note3.number);
  BOOST_CHECK_EQUAL(std::prev(phonebook.end())->name, note3.name);
}

BOOST_AUTO_TEST_SUITE_END()
