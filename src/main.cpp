// Copyright 2018 Davide Olgiati

#include "ui.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
      UI Interface(false);
      while (Interface.getState()) {
          Interface.Input();
      }
  } else {
    if (std::string(argv[1]) == "-d") {
      UI Interface(true);
      Interface.debug();
    } else {
      std::cout << "Invalid argument: " << argv[1]
                << std::endl
                << std::endl
                << "help:"
                << std::endl
                << "-d : run the interpreter debug"
                << "<empty> : run the interpreter";
    }
  }
  return 0;
}