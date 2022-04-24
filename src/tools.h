#ifndef _TOOLS_H
#define _TOOLS_H

#include <cmath>
#include <string>
#include <cstring>
#include <vector>

extern bool numerize(const char* x, long double * const d);
extern int MakeStrArray(const std::string input,
                        std::vector<std::string> * const output);
extern int MakeNumArray(const std::string input,
                        std::vector<long double> * const output);
extern std::string trim(std::string str);
extern std::string format(long double in);
#endif
