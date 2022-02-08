#include "parser.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <boost/io/ios_state.hpp>

std::istream& operator>>(std::istream& input, Command& command)
{
  boost::io::ios_flags_saver saver(input);
  std::string commandString;
  input >> std::noskipws >> std::ws >> commandString;
  if (!input)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  const auto parsingCommand = details::PARSING_COMMANDS.find(commandString);
  if (parsingCommand == details::PARSING_COMMANDS.end())
  {
    command = std::bind(&printError, PhoneBookUI::INVALID_COMMAND, std::placeholders::_2);
    return input;
  }
  command = parsingCommand->second(input);
  if (!input)
  {
    input.clear();
  }
  input >> details::skipWS;
  if(details::checkGarbage(input))
  {
    command = std::bind(&printError, PhoneBookUI::INVALID_COMMAND, std::placeholders::_2);
  }
  return input;
}

Command details::parseAdd(std::istream& input)
{
  PhoneBook::note_t note;
  input >> note;
  if (!input)
  {
    return std::bind(&printError, PhoneBookUI::INVALID_COMMAND, std::placeholders::_2);
  }
  return std::bind(&PhoneBookUI::add, std::placeholders::_1, note, std::placeholders::_2);
}

Command details::parseStore(std::istream& input)
{
  std::string markName;
  std::string newMarkName;
  input >> details::skipWS >> markName >> details::skipWS >> newMarkName;
  if (!input)
  {
    return std::bind(&printError, PhoneBookUI::INVALID_COMMAND, std::placeholders::_2);
  }
  return std::bind(&PhoneBookUI::store, std::placeholders::_1, markName, newMarkName, std::placeholders::_2);
}

Command details::parseInsert(std::istream& input)
{
  PhoneBook::note_t note;
  std::string position;
  std::string markName;
  input >> details::skipWS >> position;
  if (!input)
  {
    return std::bind(&printError, PhoneBookUI::INVALID_COMMAND, std::placeholders::_2);
  }
  if (!(input >> details::skipWS >> markName))
  {
    return std::bind(&printError, PhoneBookUI::INVALID_BOOKMARK, std::placeholders::_2);
  }
  if (!(input >> note))
  {
    return std::bind(&printError, PhoneBookUI::INVALID_COMMAND, std::placeholders::_2);
  }
  if (position == "after")
  {
    return std::bind(&PhoneBookUI::insert, std::placeholders::_1, PhoneBook::Position::AFTER, markName, note, std::placeholders::_2);
  }
  else if (position == "before")
  {
    return std::bind(&PhoneBookUI::insert, std::placeholders::_1, PhoneBook::Position::BEFORE, markName, note, std::placeholders::_2);
  }
  else
  {
    return std::bind(&printError, PhoneBookUI::INVALID_COMMAND, std::placeholders::_2);
  }
}

Command details::parseDeleteRecord(std::istream& input)
{
  std::string markName;
  input >> details::skipWS >> markName;
  if (!input)
  {
    return std::bind(&printError, PhoneBookUI::INVALID_BOOKMARK, std::placeholders::_2);
  }
  return std::bind(&PhoneBookUI::deleteMark, std::placeholders::_1, markName, std::placeholders::_2);
}

Command details::parseShow(std::istream& input)
{
  std::string markName;
  if (!(input >> details::skipWS >> markName))
  {
    return std::bind(&printError, PhoneBookUI::INVALID_BOOKMARK, std::placeholders::_2);
  }
  return std::bind(&PhoneBookUI::show, std::placeholders::_1, markName, std::placeholders::_2);
}

Command details::parseMove(std::istream& input)
{
  std::string markName;
  if (!(input >> details::skipWS >> markName))
  {
    return std::bind(&printError, PhoneBookUI::Error::INVALID_BOOKMARK, std::placeholders::_2);
  }
  PhoneBookUI::steps_t steps;
  if (!(input >> steps))
  {
    return std::bind(&printError, PhoneBookUI::INVALID_STEP, std::placeholders::_2);
  }
  return std::bind(&PhoneBookUI::move, std::placeholders::_1, steps, markName, std::placeholders::_2);
}

std::istream& details::skipWS(std::istream& input)
{
  while (isblank(input.peek()))
  {
    input.get();
  }
  return input;
}

bool details::checkGarbage(std::istream& input)
{
  std::string garbage;
  input >> details::skipWS;
  std::getline(input, garbage);
  return !garbage.empty() && !input.fail();
}
