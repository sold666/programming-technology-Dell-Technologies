#ifndef B3_PARSER_HPP
#define B3_PARSER_HPP

#include <functional>
#include "phonebook-interface.hpp"

using Command = std::function<void(PhoneBookUI*, std::ostream&)>;

std::istream& operator>>(std::istream&, Command&);

namespace details
{
  using ParsingCommand = std::function<Command(std::istream&)>;

  Command parseAdd(std::istream&);
  Command parseStore(std::istream&);
  Command parseInsert(std::istream&);
  Command parseDeleteRecord(std::istream&);
  Command parseShow(std::istream&);
  Command parseMove(std::istream&);

  std::istream& skipWS(std::istream&);
  bool checkGarbage(std::istream&);

  const std::unordered_map<std::string, ParsingCommand> PARSING_COMMANDS =
  {
    {"add", parseAdd},
    {"store", parseStore},
    {"insert", parseInsert},
    {"delete", parseDeleteRecord},
    {"show", parseShow},
    {"move", parseMove}
  };
}

#endif
