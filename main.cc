// Copyright 2018 Davide Olgiati

#include "Include/ui.h"

int main(int argc, char* argv[]) {
  UI *Interface;
  if (argc < 2) {
      Interface = new UI(false);
      while (Interface->getState()) {
          Interface->Input();
      }
  } else {
    if (std::string(argv[1]) == "-d") {
      Interface = new UI(true);
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
