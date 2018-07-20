// Copyright 2018 Davide Olgiati

#include "Include/debug.h"
#include "Include/catch.hpp"

bool runTests() {
  return Catch::Session().run();
}

void fail(Interpreter* const I,
          std::string test,
          std::string desc = "") {
  CHECK_FALSE(I->parse(test));
  if ("" == desc) {
    OUTPUT(test + " -> false");
  } else {
    OUTPUT(desc + " -> false");
  }
}

void pass(Interpreter* const I,
          std::string test,
          std::string result,
          std::string desc = "") {
  I->parse(test);
  REQUIRE_THAT(I->getRet(), Eq(FORMAT(result)));
  if ("" == desc) {
    OUTPUT(test);
  } else {
    OUTPUT(desc);
  }
}

TEST_CASE("Toolbox Function ciao Test", "[ciao]") {
  TITLE("Toolbox Function ciao Test");

  Interpreter I(true);
    
  pass(&I, "Ciao(Davide)", "Ciao Davide");
  fail(&I, "Caio(Davide)");
  fail(&I, "Ciao([1:100])");
  fail(&I, "Ciao(Davide, Olgiati)");
  pass(&I, "OverArrayCiao(Davide, Giorgio)", "Ciao Davide, Ciao Giorgio");
  pass(&I, "ReverseArray(OverArrayCiao(Davide, Giorgio))",
       "Ciao Giorgio, Ciao Davide");

  std::cout << "\n\n";
}

TEST_CASE("Toolbox String function Test", "[TsF]") {
  TITLE("Toolbox string funcions Test");

  Interpreter I(true);

  fail(&I, "Length([1:10]");
  fail(&I, "Length([)");
  fail(&I, "Length([1:10])");
  pass(&I, "Length(Davide)", "6");
  pass(&I, "ReverseStr(Davide)", "edivaD");
  fail(&I, "ReverseStr([1:100])");
  pass(&I, "ReverseArray([1:3])", "3, 2, 1");
  pass(&I, "OrderArray(2, 1, 3)", "1, 2, 3");
  fail(&I, "Length(Davide, Olgiati)");
  fail(&I, "ReverseStr(Davide, Olgiati)");
  pass(&I, "ReverseArray(Davide, Giorgio)", "Giorgio, Davide");
  pass(&I, "OverArrayReverseStr(Davide, Giorgio)", "edivaD, oigroiG");
  pass(&I, "OrderArray(Davide, Vittorio, Giorgio)",
       "Davide, Giorgio, Vittorio");
  pass(&I, "ReverseArray(Davide, Giorgio, Vittorio)",
       "Vittorio, Giorgio, Davide");

  std::cout << "\n\n";
}

TEST_CASE("Toolbox Array generation Test", "[array]") {
  TITLE("Toolbox array generation Test");

  Interpreter I(true);
    
  fail(&I, "[a:b");
  fail(&I, "[1:3");
  fail(&I, "[a:b]");
  fail(&I, "[a:10]");
  fail(&I, "[10:b]");
  pass(&I, "[1:10]", "1, 2, 3, 4, 5, 6, 7, 8, 9, 10");
  pass(&I, "[1:-1]", "-1, 0, 1");
  pass(&I, "[-1:10]", "-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10");
  fail(&I, "[a:b:c]");
  pass(&I, "[-1:-9]", "-9, -8, -7, -6, -5, -4, -3, -2, -1");
  fail(&I, "[1:10:2]");
  fail(&I, "[b:a:10]");
  fail(&I, "[10:a:b]");
  fail(&I, "[1:a:10]");
  fail(&I, "[a:10:c:d]");
  pass(&I, "[1:3], [4:6]", "1, 2, 3, 4, 5, 6");
  fail(&I, "[1:10][1:10]");
  fail(&I, "[1:10][a:b:c]");
  fail(&I, "[1:10]ciao(Davide)");
  pass(&I, "[1:5], Ciao(Davide)", "1, 2, 3, 4, 5, Ciao Davide");
  fail(&I, "[ciao(davide):ciao(pippo)]");

  std::cout << "\n\n";
}

TEST_CASE("Toolbox math function Test", "[MF]") {
  TITLE("Toolbox math funcions Test");

  Interpreter I(true);

  pass(&I, "+()", "0");
  pass(&I, "*()", "1");
  pass(&I, "+(1)", "1");
  pass(&I, "+(0)", "0");
  pass(&I, "*(1)", "1");
  pass(&I, "*(0)", "0");
  pass(&I, "+(1, 1)", "2");
  pass(&I, "*(1, 1)", "1");
  pass(&I, "*(5, 2)", "10");
  pass(&I, "*(0.5, 0.5)", "0.25");
  pass(&I, "+(0.5, 0.5)", "1");
  pass(&I, "+(*(), *())", "2");
  pass(&I, "+(*(0.5, 0.5), *(0.5, 0.5))", "0.5");

  std::cout << "\n\n";
}

TEST_CASE("Toolbox function over Array Test", "[FoA]") {
  TITLE("Toolbox funcions over Array Test");

  Interpreter I(true);

  pass(&I, "*([1:5])", "120");
  pass(&I, "+([1:10])", "55");
  pass(&I, "+([-1:10])", "54");
  pass(&I, "+([1:10], 0)", "55");
  pass(&I, "+([1:10], 5)", "60");
  pass(&I, "+([1:10], 0.5)", "55.5");
  pass(&I, "+([1:10], [1:10])", "110");
  pass(&I, "+([1:10], 5, [1:10])", "115");
  pass(&I, "+([1:10], 5, [1:10])", "115");
  fail(&I, "+([1:10], a, [1:10])");
  fail(&I, "*([1:10]ciao(Davide))");
  pass(&I, "*(+([1:10]), +([1:5]))", "825");

  std::cout << "\n\n";
}

TEST_CASE("Toolbox const Test", "[FoA]") {
  TITLE("Toolbox const Test");

  Interpreter I(true);

  pass(&I, "G", "6.673e-11");
  pass(&I, "e", "2.718281828459045235360287471352662498");
  pass(&I, "pi", "3.1415926535897932384626433832795028841968");

  std::cout << "\n\n";
}

TEST_CASE("Toolbox Assignment Test", "[TA]") {
  Interpreter I(true);

  SECTION("value assignament") {
    TITLE("Toolbox Assignament Test");
    I.parse("V = 3");
    pass(&I, "V", "3", "V = 3");
  }

  SECTION("constant creation") {
    I.parse("!V = 3");
    pass(&I, "V", "3", "!V = 3");
  }

  SECTION("array assignament") {
    I.parse("Var = [1:3]");
    pass(&I, "Var", "1, 2, 3", "Var = [1:3]");
  }

  SECTION("function assignament") {
    I.parse("V = ReverseArray([1:3])");
    pass(&I, "V", "3, 2, 1", "V = ReverseArray([1:3])");
  }

  SECTION("constant check") {
    I.parse("!V = 3");
    fail(&I, "V = ReverseArray([1:4])", "!V = 3 , V = ReverseArray([1:4])");
    std::cout << "\n\n";
  }
}

TEST_CASE("Toolbox null Function Test", "[null]") {
  TITLE("Toolbox null Function Test");

  Interpreter I(true);

  fail(&I, "\0", "nullstring 2");

  std::cout << "\n\n";
}
