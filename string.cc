// Copyright 2018 Davide Olgiati

#include "Include/string.h"

bool ciao(std::string input, std::string * const output) {
  std::vector<std::string> partial;
  bool ret = true;

  if (MakeStrArray(input, &partial) == 1) {
    *output = "Ciao " + input;
  } else {
    output->clear();
    ret = false;
  }

  return ret;
}

bool length(std::string input, std::string * const output) {
  std::vector<std::string> partial;
  bool ret = true;

  if (MakeStrArray(input, &partial) == 1) {
    *output = std::to_string(input.length());
  } else {
    output->clear();
    ret = false;
  }

  return ret;
}

bool ReverseStr(std::string input, std::string * const output) {
  std::vector<std::string> partial;
  bool ret = true;

  if (MakeStrArray(input, &partial) == 1) {
    *output = partial[0];
    std::reverse(output->begin(), output->end());
  } else {
    output->clear();
    ret = false;
  }
  return ret;
}

bool djb2(std::string input, std::string * const output) {
  uint64_t hash = 5381;
  // std::stringstream stream;
  for (std::size_t i = input.length(); i--;) {
    hash = ((hash << 5) + hash) + input[i];
  }
  *output = "funzione in costruzione";
  // stream << "0x" << std::hex << hash;
  // *output = stream.str();
  return true;
}

bool OverArrayCiao(std::string input, std::string * const output) {
  std::vector<std::string> partial;
  bool ret = true;

  if (MakeStrArray(input, &partial) >= 1) {
    *output = "";
    for (std::vector<std::string>::size_type i = 0; i < partial.size(); i++) {
      *output += "Ciao " + trim(partial[i]);
      if (i < partial.size() - 1) {
        *output += ", ";
      }
    }
  } else {
    output->clear();
    ret = false;
  }

  return ret;
}

bool OverArrayReverseStr(std::string input, std::string * const output) {
  std::vector<std::string> partial;
  bool ret = true;

  if (MakeStrArray(input, &partial) >= 1) {
    *output = "";
    std::string app = "";
    for (std::vector<std::string>::size_type i = 0; i < partial.size(); i++) {
      app = trim(partial[i]);
      std::reverse(app.begin(), app.end());
      *output += app;
      if (i < partial.size() - 1) {
        *output += ", ";
      }
    }
  } else {
    output->clear();
    ret = false;
  }

  return ret;
}

bool ReverseArray(std::string input, std::string * const output) {
  std::vector<std::string> partial;
  bool ret = true;

  if (MakeStrArray(input, &partial) >= 1) {
    *output = "";
    for (std::vector<std::string>::size_type i = partial.size(); i--;) {
      *output += trim(partial[i]);
      if (i > 0) {
        *output += ", ";
      }
    }
  } else {
    output->clear();
    ret = false;
  }

  return ret;
}

bool OrderArray(std::string input, std::string * const output) {
  std::vector<std::string> partial;
  bool ret = true;

  if (MakeStrArray(input, &partial) >= 1) {
    *output = "";
    for (std::vector<std::string>::size_type i = partial.size(); i--;) {
      partial[i] = trim(partial[i]);
    }

    std::sort(partial.begin(),
              partial.end(),
              std::greater_equal<std::string>());

    for (std::vector<std::string>::size_type i = partial.size(); i--;) {
      *output += partial[i];
      if (i > 0) {
        *output += ", ";
      }
    }
  } else {
    output->clear();
    ret = false;
  }

  return ret;
}
