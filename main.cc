// Copyright 2018 Davide Olgiati

#include "include/header/interpreter.h"
#include "include/header/math.h"
#include "include/header/string.h"
#include "include/header/debug.h"

bool populate(interpreter* const I);

bool populate(interpreter* const I) {
  bool ret = true;

  ret &= I->add("Ciao",
                ciao,
                "scrive Ciao <arg>");
  ret &= I->add("ReverseStr",
                ReverseStr,
                "scrive <arg> al contrario");
  ret &= I->add("Length",
                length,
                "ritorna la lunghrzza di <arg>");
  ret &= I->add("+",
                sum,
                "somma un numero variabile di argomenti >= 0");
  ret &= I->add("*",
                mul,
                "moltiplica un numero variabile di argomenti >= 0");
  ret &= I->add("OverArrayCiao",
                OverArrayCiao,
                "applica la funzione \"ciao\" su un array");
  ret &= I->add("ReverseArray",
                ReverseArray,
                "rigira l'array");
  ret &= I->add("/",
                divide,
                "divide un numero variabile di argomenti, eventualmente 0");
  ret &= I->add("OverArrayReverseStr",
                OverArrayReverseStr,
                "applica la funzione reverse su un array");
  ret &= I->add("OrderArray",
                OrderArray,
                "ordina un array");
  ret &= I->add("Sqrt",
                squareroot,
                "ritorna la radice quadrata degli argomenti, eventualmente 1");
  ret &= I->add("Binomial",
                binomial,
                "ritorna il binomiale degli argomenti, 2");
  // I.add("log",
  //       logarithm,
  //       "ritorna il logaritmo naturale degli argomenti, eventualmente 1");
  // I.add("log2",
  //       logarithm2,
  //       "ritorna il logaritmo base 2 degli argomenti, eventualmente 1");
  // I.add("log10",
  //       logarithm10,
  //       "ritorna il logaritmo base 10 degli argomenti, eventualmente 1");

  return ret;
}

int main(int argc, char* argv[]) {
  int res = 0;
  if (argc < 2) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    interpreter I;
    std::string str = "true";

    if (populate(&I)) {
      do {
        res = I.parse(str);
        std::cout << ((res) ? ("\n" + str + " = " + I.getRet()) :
                      (I.getRet()))
                  << std::endl
                  << std::endl;
        std::cout << ((res) ? ("[\e[32mT\e[0m] >> ") : ("[\e[31mT\e[0m] >> "));
        std::fflush(stdin);
        std::getline(std::cin, str);
      } while (str != ":exit");
      res = 0;
    } else {
      std::cout << "\e[1;7;31mERROR OCCURED WHILE POPULATING\e[0m"
                << std::endl
                << std::endl;
      res = -1;
    }
  } else {
    if (std::string(argv[1]) == "-d") {
      res = runTests();
    } else {
      std::cout << "Invalid argument: " << argv[1]
                << std::endl
                << std::endl
                << "help:"
                << std::endl
                << "-d : run the interpreter debug"
                << "<empty> : run the interpreter";
      res = -1;
    }
  }
  return res;
}
