// Copyright 2018 Davide Olgiati

#ifndef _INTERPRETER_H
#define _INTERPRETER_H

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
#include "math.h"
#include "string.h"

struct Return {
    std::string arg;
    bool success;
};

typedef std::function< bool(std::string, std::string * const) > Function;
typedef std::unordered_map<std::string, std::string> stringmap;

class Interpreter {
 public:
  Interpreter();
  bool add(std::string x, Function funct, std::string info = "");
  bool parse(std::string start, bool recursive = false);
  void debug();
  void nodebug();
  Return getRet();
  int getMemUsage();
    
 private:
  struct Argument {
    std::string value;
    bool write;
  };

  typedef std::unordered_map<std::string, Argument> varmap;

  bool populate();
  bool isFunct(std::string input);
  bool isAssign(std::string input);
  bool isAtoms(const std::string input);
  bool isAtom(const std::string str);
  void debug(std::string str);
  std::string expand(std::string x);
  int isBalanced(std::string str);
  std::string mapinfo();
  std::string varinfo();

  std::unordered_map< std::string, Function > functions;
  stringmap infos;
  varmap varMap;
  bool dbg;
  unsigned int tab;
  Return lst;

  static const char T[];
  static const char Tf[];
  static const char F[];
  static const char Ff[];
  static const char GG[];
  static const char PF[];
};

#endif  // _INTERPRETER_H
