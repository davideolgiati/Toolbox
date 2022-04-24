// Copyright 2018 Davide Olgiati

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <cstring>
#include <stdio.h>
#include <string.h>

#include <regex>

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <functional>
#include <iomanip>
#include <vector>
#include <chrono>
#include <ncurses.h>
#include "tools.h"

typedef std::function<bool(std::string, std::string * const)> function;

class functions {
private:
    std::regex function_structure_regex = std::regex("^\\w+\\(\\s*\\w*\\s*(,\\s*\\w+\\s*)*\\)$");
    std::unordered_map<std::string, function> _functions;

public:
  bool set(std::string id, function funct);
  function get(std::string id);
  bool parse(std::string input);
};

#endif // _FUNCTIONS_H