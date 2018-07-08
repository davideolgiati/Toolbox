// Copyright 2018 Davide Olgiati

#include "header/tools.h"

bool numerize(const char * x, long double * const d) {
  bool ret = false;
  char * end;
  // Trim leading space
  while (isspace((unsigned char)*x)) x++;

  if (0 != *x) {
    // Trim trailing space
    end = const_cast<char*>(reinterpret_cast<const char*>(x + strlen(x) - 1));
    while (end > x && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;
    bool num = true;
    char * p = const_cast<char*>(reinterpret_cast<const char*>(x));
    bool dotTest = true;
    if ('+' == *p || '-' == *p) p++;
    while (*p) {
      num &= ((('9' + 1) > *p && ('0' - 1) < *p)
              || ('.' == *p && dotTest)
              || ('e' == *p));
      if ('.' == *p)
        dotTest = false;
      if ('e' == *p && ('+' == *(p + 1) || '-' == *(p + 1)))
        p++;
      p++;
    }

    ret = num;

    if (num)
      sscanf(x, "%Lf", d);
  }
  return ret;
}

int MakeStrArray(const std::string input,
                 std::vector<std::string> * const output) {
  // Strtok
  static const char delim = ',';
  char * dup = strdup(input.c_str());
  char * token = std::strtok(dup, &delim);
  int size = 0;

  while (NULL != token) {
    output->push_back(std::string(token));
    size++;
    token = std::strtok(NULL, &delim);
  }

  free(dup);

  return size;
}

int MakeNumArray(const std::string input,
                 std::vector<long double> * const output) {
  std::vector<std::string> partial;
  int size = MakeStrArray(input, &partial);
  long double next = 0;
  bool res = true;

  for (std::vector<std::string>::size_type i = 0;
       i < partial.size() && res;
       i++) {
    res &= numerize(partial[i].c_str(), &next);
    if (res) {
      output->push_back(next);
    }
  }

  if (res) {
    return size;
  } else {
    output->clear();
    return -1;
  }
}

std::string trim(std::string str) {
  if (str.empty()) return str;
  const std::size_t firstScan = str.find_first_not_of(' ');
  const std::size_t first = ((firstScan == std::string::npos) ?
                             str.length() :
                             firstScan);
  const std::size_t last = str.find_last_not_of(' ');
  return str.substr(first, last-first+1);
}

std::string format(long double in) {
  std::string out = "\0";
  char buffer[32];
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%Lf", in);
  out = std::string(buffer);
  while (out.find(".") != std::string::npos &&
         (out.substr(out.length() - 1, 1) == "0" ||
          out.substr(out.length() - 1, 1) == ".")) {
    out.pop_back();
  }
  return out;
}
