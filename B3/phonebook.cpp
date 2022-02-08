#include "phonebook.hpp"
#include <sstream>
#include "phonebook-interface.hpp"
#include "parser.hpp"

std::istream& operator>>(std::istream& input, PhoneBook::note_t& note)
{
  std::string number;
  if (input.eof())
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  input >> details::skipWS >> number;
  for (auto i : number)
  {
    if (!isdigit(i))
    {
      input.setstate(std::ios_base::failbit);
      return input;
    }
  }
  bool isShielding = false;
  std::string name;
  if (input.eof())
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  char symbol;
  input >> details::skipWS >> symbol;
  if (symbol != '\"')
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  while (input.get(symbol))
  {
    if (!input)
    {
      input.setstate(std::ios_base::failbit);
      return input;
    }
    if (isShielding)
    {
      if (symbol == '\\' || symbol == '\"')
      {
        name.pop_back();
      }
      isShielding = false;
    }
    else if (symbol == '\\')
    {
      isShielding = true;
    }
    else if (symbol == '\"')
    {
      break;
    }
    name.push_back(symbol);
  }
  if ((symbol != '\"') || name.empty())
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  note.name = name;
  note.number = number;
  return input;
}

std::istream& operator>>(std::istream& input, PhoneBook::Position& place)
{
  std::string placeString;
  input >> details::skipWS >> placeString;

  if (placeString == "before")
  {
    place = PhoneBook::BEFORE;
  }
  else if (placeString == "after")
  {
    place = PhoneBook::AFTER;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::ostream &operator<<(std::ostream& out, const PhoneBook::iterator& it)
{
  return out << it->number << " " << it->name << '\n';
}

PhoneBook::iterator PhoneBook::insert(const PhoneBook::note_t& note, const PhoneBook::iterator& it, const Position pos)
{
  if(pos == AFTER)
  {
    return phoneBook_.insert(std::next(it), note);
  }
  else
  {
    return phoneBook_.insert(it, note);
  }
}

void PhoneBook::addNote(const PhoneBook::note_t& note)
{
  phoneBook_.push_back(note);
}

PhoneBook::iterator PhoneBook::deleteNote(const PhoneBook::iterator& it)
{
  return phoneBook_.erase(it);
}

PhoneBook::iterator PhoneBook::begin()
{
  return phoneBook_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return phoneBook_.end();
}

PhoneBook::const_iterator PhoneBook::cbegin() const
{
  return phoneBook_.cbegin();
}

PhoneBook::const_iterator PhoneBook::cend() const
{
  return phoneBook_.cend();
}

bool PhoneBook::isEmpty() const
{
  return phoneBook_.empty();
}
