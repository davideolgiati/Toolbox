// Copyright 2018 Davide Olgiati

#include "interpreter.h"

Interpreter::Interpreter(){
  // _infos["debug()"] = "comincia una sessione di debug";
  // _infos["nodebug()"] = "finisce la sessione di debug";
  // _infos["help()"] = "mostra queste informazioni";
  // _infos["exit()"] = "esce dal programma";
  // _infos["memusage()"] = "visualizza la memoria utilzzata dal programma";
  // _infos["listvar()"] = "mostra le variabili nel database";
  // _infos["[<s>:<e>]"] = "genera un array contenet i valori da <s> a <e>";
  // _infos["(!)<var> = <args>"] = "aggiunge un valore come costante";

  _dbg = false;
  _tab = 0;
  populate();
}

bool Interpreter::add(std::string x, Function funct, std::string info) {
  _functions[x] = funct;
  _infos[x] = info;
  return (_functions.find(x) != _functions.end());
}

bool Interpreter::parse(std::string start, bool recursive) {
  if(start == "\0" || start.empty()) {
      _lst.arg = "";
      _lst.success = false;
      return false;
  }
  const std::string str = trim(start);
  std::string ret = "";

  _tab = 0;
  _lst.arg = "";

  if ("true" == str) {
    _lst.success = true;
    return true;
  }

  if ("false" == str) {
    _lst.success = false;
    return false;
  }

  if ("help()" == str) {
    _lst.arg = mapinfo();
    _lst.success = true;
    return true;
  }

  if ("debug()" == str) {
    debug();
    return true;
  }

  if ("nodebug()" == str) {
    nodebug();
    return true;
  }

  if ("listvar()" == str) {
    _lst.arg = varinfo();
    _lst.success = true;
    return true;
  }

  if (isFunct(str)) {
    if (!recursive) {
      _lst.arg.append("\n");
      _lst.success = true;
    }
    return true;
  }

  if (isAssign(str)) {
    if (!recursive) {
      _lst.arg.append("\n");
      _lst.success = true;
    }
    return true;
  }

  if (isAtoms(str)) {
    if (!recursive) {
      _lst.arg.append("\n");
      _lst.success = true;
    }
    return true;
  }

  _lst.arg = "";
  _lst.success = false;
  return false;
}

void Interpreter::debug() {
  _lst.arg = "";
  _lst.success = true;
  _dbg = true;
}

void Interpreter::nodebug() {
  _lst.arg = "";
  _lst.success = true;
  _dbg = false;
}

Return Interpreter::getRet() const {
  return _lst;
}

int Interpreter::getMemUsage() const {
    int size = 0;
    int bitCounter = 1;

    size += sizeof(_tab);
    size += _lst.arg.size();

    for (const auto& n : _functions) {
        size += n.first.size();
        size += sizeof(Function);
    }

    for (const auto& n : _infos) {
        size += n.first.size();
        size += n.second.size();
    }

    for (const auto& n : _varMap) {
        size += n.first.size();
        size += n.second.value.size();
        bitCounter++;
    }

    return size + std::floor(bitCounter/8);
}

bool Interpreter::populate() {
    bool ret = true;

    // ret &= add("Ciao",
    //               ciao,
    //               "scrive Ciao <arg>");
    // ret &= add("ReverseStr",
    //               ReverseStr,
    //               "scrive <arg> al contrario");
    // ret &= add("Length",
    //               length,
    //               "ritorna la lunghrzza di <arg>");
    // ret &= add("+",
    //               sum,
    //               "somma un numero variabile di argomenti >= 0");
    // ret &= add("*",
    //               mul,
    //               "moltiplica un numero variabile di argomenti >= 0");
    // ret &= add("OverArrayCiao",
    //               OverArrayCiao,
    //               "applica la funzione \"ciao\" su un array");
    // ret &= add("ReverseArray",
    //               ReverseArray,
    //               "rigira l'array");
    // ret &= add("/",
    //               divide,
    //               "divide un numero variabile di argomenti >=0");
    // ret &= add("OverArrayReverseStr",
    //               OverArrayReverseStr,
    //               "applica la funzione reverse su un array");
    // ret &= add("OrderArray",
    //               OrderArray,
    //               "ordina un array");
    // ret &= add("Sqrt",
    //               squareroot,
    //               "ritorna la radice quadrata degli argomenti >= 1");
    // ret &= add("Binomial",
    //               binomial,
    //               "ritorna il binomiale degli argomenti, 2");
    // ret &= add("Factorial",
    //            FactorialHandler,
    //            "ritorna il fattoriale degli argomenti >= 1");
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

  _tab++;

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

  if (_functions.find(funct) == _functions.end()) {
      debug("[" + funct + "] is not recognasied as a valid function");
      return false;
  }

  _tab--;

  return _functions[funct](_lst.arg, &_lst.arg);
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

    if (_varMap.find(Fvar) != _varMap.end() &&
        !_varMap[Fvar].write) {
      _lst.arg = "la variabile " + Fvar + " è una costante\n";
      _lst.success = false;
      return false;
    }

    _varMap[Fvar].value = trim(tok[1]);
    _varMap[Fvar].write = RW;
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

  _tab++;
  std::string current = "";
  std::vector<std::string>::size_type i = 0;
  const std::vector<std::string>::size_type end = tokens.size() - 1;
  for (auto tok : tokens) {
    if(ret){
        current = expand(tok);

        if (0 != current.compare(tok)) {
            out += compose(current, i, end);
        } else {
            if (isAtom(tok)) {
                out += compose(_lst.arg, i, end);
            } else if (isFunct(tok)) {
                out += compose(_lst.arg, i, end);
            } else {
                ret = false;
            }
        }
    }
    i++;
  }

  current = "";

  _tab--;

  _lst.arg = (ret) ? out : "null";
  return ret;
}

std::string Interpreter::compose(std::string x, std::vector<std::string>::size_type pos, std::vector<std::string>::size_type end){
    if (pos != end)
        x += ", ";
    return x;
}

bool Interpreter::isAtom(const std::string args) {
  debug("checking if [" + args + "] is atomic");
  _tab++;

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
    if (_varMap.find(args) == _varMap.end())
      _lst.arg = args;
    else
      test &= parse(_varMap[args].value, true);
    debug("[" + _lst.arg + "] is an atom!");
  } else {
    debug("[" + args + "] is not atom!");
    _lst.arg = "";
  }

  _tab--;

  return test;
}

void Interpreter::debug(std::string str) {
  if (_dbg) {
    std::string tabs = "";
    for (unsigned int i = 0; i < _tab; i++) {
      if (9 < i)
        tabs += "  ";
      else
        tabs += " ";
    }
    printw("%s\n", (tabs + str).c_str());
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

std::string Interpreter::mapinfo() const {
  std::stringstream out;
  std::vector<std::string> VoS;
  int max_length = 25;

  for (auto iter : _infos) {
    out << std::left
        << std::setfill(' ')
        << std::setw(max_length + 1)
        << "  " + iter.first
        << "  " + iter.second;

    VoS.push_back(out.str());
    out.str("");
  }

  std::sort(VoS.begin(), VoS.end(), std::greater<std::string>());

  for (auto iter : VoS) {
    out << iter
        << std::endl;
  }

  return out.str() + "\n\n";
}

std::string Interpreter::varinfo() const {
  std::stringstream out;

  for (auto iter : _varMap) {
    out << ((iter.second.write) ?
            ("        ") :
            (" const  "))
        << std::left
        << std::setfill(' ')
        << std::setw(20)
        << iter.first
        << iter.second.value
        << std::endl;
  }

  return out.str() + "\n";
}
