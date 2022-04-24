// Copyright 2018 Davide Olgiati

#ifndef _STRING_H
#define _STRING_H

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>
#include "tools.h"

extern bool ciao(std::string input, std::string * const output);
extern bool ReverseStr(std::string input, std::string * const output);
extern bool djb2(std::string input, std::string * const output);
extern bool length(std::string input, std::string * const output);
extern bool OverArrayCiao(std::string input, std::string * const output);
extern bool OverArrayReverseStr(std::string input, std::string * const output);
extern bool ReverseArray(std::string input, std::string * const output);
extern bool OrderArray(std::string input, std::string * const output);

#endif  // _STRING_H
