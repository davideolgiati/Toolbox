// Copyright 2018 Davide Olgiati

#include "Include/interpreter.h"

const char Interpreter::T[] = "true.";
const char Interpreter::Tf[] = "\e[1;7;32mtrue.\e[0m";
const char Interpreter::F[] = "false.";
const char Interpreter::Ff[] = "\e[1;7;31mfalse.\e[0m";
const char Interpreter::GG[] = "\n[Chorus]\n"
  "Gucci gang, Gucci gang, Gucci gang, Gucci gang (Gucci gang)\n"
  "Gucci gang, Gucci gang, Gucci gang (Gucci gang)\n"
  "Spend three racks on a new chain (yuh)\n"
  "My bitch love do cocaine, ooh (ooh)\n"
  "I fuck a bitch, I forgot her name (brr, yuh)\n"
  "I can't buy a bitch no wedding ring (ooh)\n"
  "Rather go and buy Balmains (brr)\n"
  "Gucci gang, Gucci gang, Gucci gang (Gucci gang)\n"
  "Gucci gang, Gucci gang, Gucci gang, Gucci gang (Gucci gang)\n";

Interpreter::Interpreter(bool debug)
  : lst("null") {
  infos[":debug"] = "comincia una sessione di debug";
  infos[":nodebug"] = "finisce la sessione di debug";
  infos[":help"] = "mostra queste informazioni";
  infos[":exit"] = "esce dal programma";
  infos[":listvar"] = "mostra le variabili nel database";
  infos[":eskere"] = "let's get it!";
  infos["[<s>:<e>]"] = "genera un array contenet i valori da <s> a <e>";
  infos["(!)<var> = <args>"] = "aggiunge un valore come costante";

  Argument base;
  base.write = false;
  base.value = "2.718281828459045235360287471352662498";
  varMap["e"] = base;
  base.value = "3.1415926535897932384626433832795028841968";
  varMap["pi"] = base;
  base.value = "1.61803398874989484820";
  varMap["phi"] = base;
  base.value = "6.02205e+23";
  varMap["avogadro"] = base;
  base.value = "299792458";
  varMap["speed_of_light"] = base;
  base.value = "6.673e-11";
  varMap["G"] = base;
  base.value = "0.3";
  varMap["toolbox_ver"] = base;
  base.value = "THO";
  varMap["toolbox_father"] = base;
#ifdef _WIN32
  base.value = "Windows";
#elif __APPLE__
  base.value = "MacOS";
#elif __linux__
  base.value = "Linux";
#endif
  varMap["toolbox_OS"] = base;
  dbg = false;
  tab = 0;
  populate();
}

bool Interpreter::add(std::string x, Function funct, std::string info) {
  functions[x] = funct;
  infos[x] = info;
  return (functions.find(x) != functions.end());
}

bool Interpreter::parse(std::string start, bool recursive) {
  if(start == "\0" || start.empty()) {
      lst = Ff;
      return false;
  }
  const std::string str = trim(start);
  std::string ret = "";

  tab = 0;
  lst = "";

  if (T == str) {
    lst = Tf;
    return true;
  }

  if (F == str) {
    lst = Ff;
    return false;
  }

  if (":eskere" == str) {
    lst = GG;
    lst.append(Tf);
    return true;
  }

  if (":help" == str) {
    lst = mapinfo();
    return true;
  }

  if (":debug" == str) {
    debug();
    return true;
  }

  if (":nodebug" == str) {
    nodebug();
    return true;
  }

  if (":listvar" == str) {
    lst = varinfo();
    return true;
  }

  if (isFunct(str)) {
    if (!recursive) {
      lst.append("\n");
      lst.append(Tf);
    }
    return true;
  }

  if (isAssign(str)) {
    if (!recursive) {
      lst.append("\n");
      lst.append(Tf);
    }
    return true;
  }

  if (isAtoms(str)) {
    if (!recursive) {
      lst.append("\n");
      lst.append(Tf);
    }
    return true;
  }

  lst = Ff;
  return false;
}

void Interpreter::debug() {
  lst = Tf;
  dbg = true;
}

void Interpreter::nodebug() {
  lst = Tf;
  dbg = false;
}

std::string Interpreter::getRet() {
  return lst;
}

bool Interpreter::populate() {
    bool ret = true;
    
    ret &= add("Ciao",
                  ciao,
                  "scrive Ciao <arg>");
    ret &= add("ReverseStr",
                  ReverseStr,
                  "scrive <arg> al contrario");
    ret &= add("Length",
                  length,
                  "ritorna la lunghrzza di <arg>");
    ret &= add("+",
                  sum,
                  "somma un numero variabile di argomenti >= 0");
    ret &= add("*",
                  mul,
                  "moltiplica un numero variabile di argomenti >= 0");
    ret &= add("OverArrayCiao",
                  OverArrayCiao,
                  "applica la funzione \"ciao\" su un array");
    ret &= add("ReverseArray",
                  ReverseArray,
                  "rigira l'array");
    ret &= add("/",
                  divide,
                  "divide un numero variabile di argomenti, eventualmente 0");
    ret &= add("OverArrayReverseStr",
                  OverArrayReverseStr,
                  "applica la funzione reverse su un array");
    ret &= add("OrderArray",
                  OrderArray,
                  "ordina un array");
    ret &= add("Sqrt",
                  squareroot,
                  "ritorna la radice quadrata degli argomenti, eventualmente 1");
    ret &= add("Binomial",
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

bool Interpreter::isFunct(std::string input) {
  const size_t openP = input.find('(');
  const size_t closeP = input.find_last_of(')');

  if (std::string::npos != input.find('='))
    return false;

  debug("checking for function [" + input + "]");

  tab++;

  if (std::string::npos == openP ||
      std::string::npos == closeP ||
      closeP != input.size()-1) {
    debug("parentesis error [" + input + "]");
    return false;
  }

  if (closeP < openP) {
    debug("parentesis order error [" + input + "]");
    return false;
  }

  const std::string funct = trim(input.substr(0, openP));
  const std::string args = trim(input.substr(openP+1, closeP-openP-1));

  if (!isAtoms(args)) {
    return false;
  }

  if (functions.find(funct) == functions.end()) {
      debug("[" + funct + "] is not recognasied as a valid function");
      return false;
  }

  tab--;

  return functions[funct](lst, &lst);
}

bool Interpreter::isAssign(std::string input) {
  debug("checking if [" + input + "] is an assignament");

  // Strtok
  static const char delim = '=';
  char * dup = strdup(trim(input).c_str());
  char * token = std::strtok(dup, &delim);

  // Tokens
  std::string tok[2];
  unsigned int i = 0;

  while (NULL != token && 2 > i) {
    tok[i] = std::string(token);
    i++;

    // the call is treated as a subsequent calls to strtok:
    // the function continues from where it left in previous invocation
    token = std::strtok(NULL, &delim);
  }

  free(dup);

  if (2 == i) {
    if (!isAtom(tok[0])) {
      debug("variable name [" + tok[0] + "] is not atomic");
      return false;
    }

    if (!isAtoms(tok[1])) {
      debug("[" + tok[1] + "] arguments are not atomic");
      return false;
    }

    debug("Value    = [" + tok[1] + "]\nVariable = [" + tok[0] + "]");

    const bool RW = (tok[0][0] != '!');
    std::string Fvar = trim((tok[0][0] != '!') ? tok[0] : tok[0].substr(1));

    if (varMap.find(Fvar) != varMap.end() &&
        !varMap[Fvar].write) {
      lst = "la variabile " + Fvar + " è una costante\n" + Ff;
      return false;
    }

    varMap[Fvar].value = trim(tok[1]);
    varMap[Fvar].write = RW;
    return true;
  }

  return false;
}

bool Interpreter::isAtoms(const std::string input) {
  bool ret = true;

  // Strtok
  static const char delim = ',';
  char * dup = strdup(input.c_str());
  char * token = std::strtok(dup, &delim);

  // Tokens
  std::string partial = "";
  std::vector<std::string> tokens;
  std::string out = "";

  while (NULL != token) {
    partial = std::string(token);
    partial = (0 == isBalanced(partial)) ? trim(partial) : (partial + ",");
    while (0 != isBalanced(partial) && NULL != token) {
      token = std::strtok(NULL, &delim);
      if (NULL != token) {
        partial += std::string(token);
        partial = (0 == isBalanced(partial)) ? trim(partial) : (partial + ",");
      }
    }

    tokens.push_back(partial);

    debug("found token [" + partial + "]");

    // the call is treated as a subsequent calls to strtok:
    // the function continues from where it left in previous invocation
    if (NULL != token)
      token = std::strtok(NULL, &delim);
  }

  free(dup);

  tab++;
  std::string current = "";
  std::vector<std::string>::size_type i = 0;
  for (i = 0; i < tokens.size(); i++) {
    current = expand(tokens[i]);

    if (0 != current.compare(tokens[i])) {
      out += current;
      if (i != tokens.size() - 1)
        out += ", ";
      ret &= true;
    } else {
      if (isAtom(tokens[i])) {
        debug("running atomic check over token [" + tokens[i] + "]");
        out += lst;
        if (i != tokens.size() - 1)
          out += ", ";
        ret &= true;
      } else if (isFunct(tokens[i])) {
        debug("running function check over token [" + tokens[i] + "]");
        out += lst;
        if (i != tokens.size() - 1)
          out += ", ";
        ret &= true;
      } else {
        ret &= false;
      }
    }
  }

  current = "";

  tab--;

  lst = (ret) ? out : "null";
  return ret;
}

bool Interpreter::isAtom(const std::string args) {
  debug("checking if [" + args + "] is atomic");
  tab++;

  bool test = true;
  size_t i = 0;
  for (i = 0; i < args.length(); i++) {
    test &= (args[i] != '(' &&
             args[i] != ')' &&
             args[i] != '=' &&
             args[i] != '[' &&
             args[i] != ']' &&
             args[i] != ',');
  }

  if (test) {
    if (varMap.find(args) == varMap.end())
      lst = args;
    else
      test &= parse(varMap[args].value, true);
    debug("[" + lst + "] is an atom!");
  } else {
    debug("[" + args + "] is not atom!");
    lst = "null";
  }

  tab--;

  return test;
}

void Interpreter::debug(std::string str) {
  if (dbg) {
    std::string tabs = "";
    for (unsigned int i = 0; i < tab; i++) {
      if (9 < i)
        tabs += "  ";
      else
        tabs += " ";
    }
    std::cout << tabs << str << std::endl;
  }
}

std::string Interpreter::expand(const std::string x) {
  const std::string args = trim(x);

  if ('[' == args[0] && ']' == args.back()) {
    // Strtok
    static const char delim = ':';
    char * dup = strdup(args.substr(1, args.length()-2).c_str());
    char * token = std::strtok(dup, &delim);

    // Tokens
    std::string tok[2] = {"", ""};
    unsigned int i = 0;
    bool test = true;
    size_t index = 0;

    while (NULL != token) {
      if (2 > i) {
        tok[i] = std::string(token);
        if (('+' == tok[i][0] || '-' == tok[i][0]) && (1 < tok[i].size()))
          index = 1;
        for (; index < tok[i].size(); index++)
          test &= isdigit(tok[i][index]);
        index = 0;
      }
      i++;

      // the call is treated as a subsequent calls to strtok:
      // the function continues from where it left in previous invocation
      token = std::strtok(NULL, &delim);
    }

    free(dup);

    if (3 > i && test) {
      try {
        std::string ret = "";
        const int64_t start = std::atoi(tok[0].c_str());
        const int64_t end = std::atoi(tok[1].c_str());

        if (start > end) {
          for (int64_t i = end; i <= start; ++i) {
            ret += std::to_string(i);
            if (i != start) {
              ret += ", ";
            }
          }
        } else {
          for (int64_t i = start; i <= end; ++i) {
            ret += std::to_string(i);
            if (i != end) {
              ret += ", ";
            }
          }
        }
        return ret;
      }
      catch (std::exception& e) {
        return x;
      }
    }
  }
  return x;
}

int Interpreter::isBalanced(std::string str) {
  int i = 0;
  for (size_t x = 0; x < str.length() && i > -1; x++) {
    switch (str[x]) {
    case '(':
      i++;
      break;
    case ')':
      i--;
      break;
    default:
      break;
    }
  }
  return i;
}

std::string Interpreter::mapinfo() {
  std::stringstream out;
  std::vector<std::string> VoS;
  int max_length = 40;

  for (stringmap::iterator iter = infos.begin();
       iter != infos.end();
       iter++) {
    out << std::left
        << std::setfill(' ')
        << std::setw(max_length + 1)
        << "\e[7;32m ### " + iter->first
        << " ### \e[0m " + iter->second;

    VoS.push_back(out.str());
    out.str("");
  }

  std::sort(VoS.begin(), VoS.end(), std::greater<std::string>());

  for (auto iter : VoS) {
    out << iter
        << std::endl;
  }

  return "\n\n" + out.str();
}

std::string Interpreter::varinfo() {
  std::stringstream out;
  out << std::endl;

  for (varmap::iterator iter = varMap.begin();
       iter != varMap.end();
       iter++) {
    out << ((iter->second.write) ?
            (" \e[7m       \e[0m  ") :
            (" \e[7m const \e[0m  "))
        << std::left
        << std::setfill(' ')
        << std::setw(20)
        << iter->first
        << iter->second.value
        << std::endl;
  }

  return out.str().substr(0, out.str().length()-1);
}
