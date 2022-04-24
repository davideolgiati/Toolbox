// Copyright 2018 Davide Olgiati

#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <cstring>
#include <stdio.h>
#include <string.h>

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
//#include "math.h"
//#include "string.h"

struct Return {
  std::string arg;
  bool success;
};

class Interpreter {
private:
  struct Argument {
    std::string value;
    bool write;
  };

  typedef std::unordered_map<std::string, Argument> varmap;
  typedef std::function<bool(std::string, std::string * const)> Function;
  typedef std::unordered_map<std::string, std::string> stringmap;

  bool populate();
  bool isFunct(std::string input);
  bool isAssign(std::string input);
  bool isAtoms(const std::string input);
  bool isAtom(const std::string str);
  void debug(std::string str);
  std::string expand(std::string x);
  std::string compose(std::string x, std::vector<std::string>::size_type pos, std::vector<std::string>::size_type end);
  int isBalanced(std::string str);
  std::string mapinfo() const;
  std::string varinfo() const;

  std::unordered_map<std::string, Function> _functions;
  stringmap _infos;
  varmap _varMap;
  bool _dbg;
  unsigned int _tab;
  Return _lst;

  static const char _T[];
  static const char _Tf[];
  static const char _F[];
  static const char _Ff[];

public:
  Interpreter();
  bool add(std::string x, Function funct, std::string info = "");
  bool parse(std::string start, bool recursive = false);
  void debug();
  void nodebug();
  Return getRet() const;
  int getMemUsage() const;
};

#endif  // _INTERPRETER_H