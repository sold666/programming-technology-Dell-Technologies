#ifndef B3_PHONEBOOK_INTERFACE_HPP
#define B3_PHONEBOOK_INTERFACE_HPP

#include <ostream>
#include <string>
#include <unordered_map>
#include "phonebook.hpp"

class PhoneBookUI
{
public:
  struct steps_t
  {
    enum Steps
    {
      FIRST,
      LAST
    };
    enum StepsFlag
    {
      NUMERIC,
      WORD,
      INVALID
    };
    union
    {
      Steps steps;
      std::iterator_traits<PhoneBook::iterator>::difference_type num;
    };
    StepsFlag flag;
  };

  enum Error
  {
    EMPTY,
    INVALID_STEP,
    INVALID_COMMAND,
    INVALID_BOOKMARK
  };

  using map = std::unordered_map<std::string, PhoneBook::iterator>;

  PhoneBookUI();
  friend std::istream& operator>>(std::istream&, steps_t&);
  void add(const PhoneBook::note_t&, std::ostream&);
  void store(const std::string&, const std::string&, std::ostream&);
  void insert(const PhoneBook::Position&, const std::string&, const PhoneBook::note_t&, std::ostream&);
  void deleteMark(const std::string&, std::ostream&);
  void show(const std::string&, std::ostream&) const;
  void move(const steps_t&, const std::string&, std::ostream&);

private:
  PhoneBook phoneBook;
  map bookmarks_;
  void moveMarks();
};

void printError(const PhoneBookUI::Error&, std::ostream&);

#endif
