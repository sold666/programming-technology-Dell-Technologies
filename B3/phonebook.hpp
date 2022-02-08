#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include <string>
#include <list>

class PhoneBook
{
public:
  struct note_t
  {
    std::string name;
    std::string number;
  };

  enum Position
  {
    AFTER,
    BEFORE
  };

  using iterator = std::list<note_t>::iterator;
  using const_iterator = std::list<note_t>::const_iterator;
  friend std::istream& operator>>(std::istream&, Position&);
  friend std::istream& operator>>(std::istream&, PhoneBook::note_t&);
  friend std::ostream& operator<< (std::ostream&, const iterator&);
  PhoneBook::iterator insert(const note_t&, const iterator&, const Position);
  PhoneBook::iterator deleteNote(const iterator&);
  void addNote(const note_t&);
  bool isEmpty() const;
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

private:
  std::list<note_t> phoneBook_;
};

#endif
