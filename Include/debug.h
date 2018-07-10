// Copyright 2018 Davide Olgiati
#ifndef _DEBUG_H
#define _DEBUG_H
#define CATCH_CONFIG_RUNNER

#include "interpreter.h"

#define OUTPUT(x) std::cout << "\t\e[1;7;32m PASS \e[0m\t" << x << std::endl
#define TITLE(x) std::cout << "\e[1;7;32m " << x << " \e[0m\n\n"
#define FORMAT(x) x + "\n\e[1;7;32mtrue.\e[0m"
#define Eq Catch::Matchers::Equals

extern void fail(Interpreter * const I, std::string test, std::string desc);
extern void pass(Interpreter * const I, std::string test, std::string result, std::string desc);
extern bool runTests();

#endif
