#include "phonebook-interface.hpp"
#include <sstream>
#include <algorithm>
#include "parser.hpp"

PhoneBookUI::PhoneBookUI()
{
  bookmarks_ = {{"current", phoneBook.begin()}};
}

std::istream& operator>>(std::istream& input, PhoneBookUI::steps_t& steps)
{
  std::string stepsString;
  input >> details::skipWS >> stepsString;
  if (stepsString.empty())
  {
    input.setstate(std::ios::failbit);
    steps.flag = PhoneBookUI::steps_t::INVALID;
    return input;
  }
  if (stepsString == "first")
  {
    steps.steps = PhoneBookUI::steps_t::FIRST;
    steps.flag = PhoneBookUI::steps_t::WORD;
  }
  else if (stepsString == "last")
  {
    steps.steps = PhoneBookUI::steps_t::LAST;
    steps.flag = PhoneBookUI::steps_t::WORD;
  }
  else
  {
    std::istringstream stream(stepsString);
    std::iterator_traits<PhoneBook::iterator>::difference_type num;
    stream >> num;
    if (!stream.eof())
    {
      input.setstate(std::ios::failbit);
      steps.flag = PhoneBookUI::steps_t::INVALID;
      return input;
    }
    steps.num = num;
    steps.flag = PhoneBookUI::steps_t::NUMERIC;
  }
  return input;
}

void printError(const PhoneBookUI::Error& error, std::ostream& out)
{
  if (error == PhoneBookUI::EMPTY)
  {
    out << "<EMPTY>" << '\n';
  }
  else if (error == PhoneBookUI::INVALID_STEP)
  {
    out << "<INVALID STEP>" << '\n';
  }
  else if (error == PhoneBookUI::INVALID_COMMAND)
  {
    out << "<INVALID COMMAND>" << '\n';
  }
  else if (error == PhoneBookUI::INVALID_BOOKMARK)
  {
    out << "<INVALID BOOKMARK>" << '\n';
  }
}

void PhoneBookUI::add(const PhoneBook::note_t& note, std::ostream&)
{
  const bool empty = phoneBook.isEmpty();
  phoneBook.addNote(note);
  if (empty)
  {
    moveMarks();
  }
}

void PhoneBookUI::store(const std::string& oldName, const std::string& newName, std::ostream& out)
{
  const auto it = bookmarks_.find(oldName);
  if (it != bookmarks_.end())
  {
    bookmarks_.insert({newName, it->second});
  }
  else
  {
    printError(INVALID_BOOKMARK, out);
  }
}

void PhoneBookUI::insert(const PhoneBook::Position& position, const std::string& markName,
    const PhoneBook::note_t& note, std::ostream& out)
{
  const auto it = bookmarks_.find(markName);

  if (it == bookmarks_.end())
  {
    printError(INVALID_BOOKMARK, out);
    return;
  }
  const bool empty = phoneBook.isEmpty();
  if(position == PhoneBook::AFTER)
  {
    phoneBook.insert(note, it->second, position);
  }
  else if (position == PhoneBook::BEFORE)
  {
    phoneBook.insert(note, it->second, position);
  }
  if (empty)
  {
    moveMarks();
  }
}

void PhoneBookUI::deleteMark(const std::string& markName, std::ostream& out)
{
  if (phoneBook.isEmpty())
  {
    printError(EMPTY, out);
    return;
  }
  const auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    printError(INVALID_BOOKMARK, out);
    return;
  }
  const auto deletedIter = it->second;
  for (auto& bookmark : bookmarks_)
  {
    if (deletedIter == bookmark.second)
    {
      if ((std::next(bookmark.second) != phoneBook.end()) || (bookmark.second == phoneBook.begin()))
      {
        ++bookmark.second;
      }
      else
      {
        --bookmark.second;
      }
    }
  }
  phoneBook.deleteNote(deletedIter);
}

void PhoneBookUI::show(const std::string& markName, std::ostream& out) const
{
  const auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    printError(INVALID_BOOKMARK, out);
    return;
  }
  if (phoneBook.isEmpty())
  {
    printError(EMPTY, out);
    return;
  }
  out << it->second;
}

void PhoneBookUI::move(const PhoneBookUI::steps_t& steps, const std::string& markName, std::ostream & out)
{
  const auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    printError(INVALID_BOOKMARK, out);
    return;
  }
  if (steps.flag == steps_t::INVALID)
  {
    printError(INVALID_STEP, out);
    return;
  }
  if (steps.flag == steps_t::NUMERIC)
  {
    auto itNum = steps.num;
    if (steps.num > 0 && (steps.num > std::distance(it->second, phoneBook.end()) - 1))
    {
      itNum = std::min(steps.num, std::distance(it->second, phoneBook.end()) - 1);
    }
    if (-steps.num > std::distance(it->second, phoneBook.begin()))
    {
      itNum = std::max(steps.num, -std::distance(phoneBook.begin(), it->second));
    }
    std::advance(bookmarks_[markName], itNum);
  }
  else if (steps.steps == steps_t::FIRST)
  {
    bookmarks_[markName] = phoneBook.begin();
  }
  else
  {
    bookmarks_[markName] = std::prev(phoneBook.end());
  }
}

void PhoneBookUI::moveMarks()
{
  if (phoneBook.isEmpty())
  {
    return;
  }
  for (auto & bookmark : bookmarks_)
  {
    if (bookmark.second == phoneBook.end())
    {
      bookmark.second--;
    }
  }
}
