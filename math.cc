// Copyright 2018 Davide Olgiati

#include "header/math.h"

bool sum(const std::string input, std::string * const output) {
  if ("" == input) {
    *output = "0";
    return true;
  }

  std::vector<long double> numbers;
  int size = MakeNumArray(input, &numbers);
  bool ret = true;

  if (size >= 0) {
    long double out = 0;

    for (std::vector<long double>::size_type i = 0; i < numbers.size(); i++) {
      out += numbers[i];
    }

    *output = format(out);
  } else {
    *output = "null";
    ret = false;
  }

  return ret;
}

bool mul(const std::string input, std::string * const output) {
  if ("" == input) {
    // If mul is called with no argument we will set output to "1"
    * output = "1";
    return true;  // and true
  }

  std::vector<long double> numbers;
  int size = MakeNumArray(input, &numbers);
  bool ret = true;

  if (0 <= size) {
    long double out = 1;

    for (std::vector<long double>::size_type i = 0; i < numbers.size(); i++) {
      out *= numbers[i];
    }

    *output = format(out);
  } else {
    *output = "null";
    ret = false;
  }

  return ret;
}

bool divide(const std::string input, std::string * const output) {
  if ("" == input) {
    * output = "1";
    return true;
  }

  std::vector<long double> numbers;
  int size = MakeNumArray(input, &numbers);
  bool ret = true;

  if (0 <= size) {
    long double out = 0;

    for (std::vector<long double>::size_type i = 0; i < numbers.size(); i++) {
      if (0 == std::fabs(out)) {
        out = numbers[i];
      } else {
        out /= numbers[i];
      }
    }

    *output = format(out);
  } else {
    *output = "null";
    ret = false;
  }

  return ret;
}

bool squareroot(const std::string input, std::string * const output) {
  if ("" == input) {
    * output = "1";
    return true;
  }

  std::vector<long double> numbers;
  int size = MakeNumArray(input, &numbers);
  bool ret = true;

  if (0 <= size) {
    *output = "";

    for (std::vector<long double>::size_type i = 0; i < numbers.size(); i++) {
      if (0 != i && i != numbers.size()) {
        * output += ", ";
      }
      if (0 == numbers[i]) {
        * output += std::to_string(numbers[i]);
      } else if (0 > numbers[i]) {
        *output = "null";
        ret = false;
        i = numbers.size() + 2;
      } else {
        * output += format(sqrt(numbers[i]));
      }
    }

  } else {
    *output = "null";
    ret = false;
  }

  return ret;
}

bool logarithm(const std::string input, std::string * const output) {
  if ("" == input) {
    * output = "1";
    return true;
  }

  std::vector<long double> numbers;
  int size = MakeNumArray(input, &numbers);
  bool ret = true;

  if (0 <= size) {
    *output = "";

    for (std::vector<long double>::size_type i = 0; i < numbers.size(); i++) {
      if (0 != i && i != numbers.size()) {
        * output += ", ";
      }
      if (0 == numbers[i]) {
        * output += std::to_string(numbers[i]);
      } else if (0 > numbers[i]) {
        *output = "null";
        ret = false;
        i = numbers.size() + 2;
      } else {
        * output += format(sqrt(numbers[i]));
      }
    }

  } else {
    *output = "null";
    ret = false;
  }

  return ret;
}

bool binomial(const std::string input, std::string * const output) {
  if ("" == input) {
    return false;
  }

  std::vector<long double> numbers;
  int size = MakeNumArray(input, &numbers);
  bool ret = true;

  if (size == 2 && numbers[0] >= numbers[1]) {
    long double out = 0;

    long double temp1 = numbers[0] - numbers[1];
    long double final1 = 1;
    long double final2 = (long double) recursiveFactorial((long long) numbers[1]);

    for(long double i = temp1 + 1; i <= numbers[0]; i += 1) {
      final1 *= i;
    }

    out = final1 / final2;

    *output = format(out);
  } else {
    *output = "null";
    ret = false;
  }

  return ret;
}

// std::string logarithm2(std::string x) {
//   if (x == "") {
//     return "1";
//   }

//   // Strtok
//   const char delim = ',';
//   char * dup = strdup(x.c_str());
//   char * token = std::strtok(dup, &delim);

//   // Tokens
//   std::string out = "";

//   while (token != NULL) {
//     out += std::to_string(log2(numerize(token)));

//     // the call is treated as a subsequent calls to strtok:
//     // the function continues from where it left in previous invocation
//     token = std::strtok(NULL, &delim);

//     if (token != NULL) {
//       out += ", ";
//     }
//   }
//   free(dup);

//   return out;
// }

// std::string logarithm10(std::string x) {
//   if (x == "") {
//     return "1";
//   }

//   // Strtok
//   const char delim = ',';
//   char * dup = strdup(x.c_str());
//   char * token = std::strtok(dup, &delim);

//   // Tokens
//   std::string out = "";

//   while (token != NULL) {
//     out += std::to_string(log10(numerize(token)));

//     // the call is treated as a subsequent calls to strtok:
//     // the function continues from where it left in previous invocation
//     token = std::strtok(NULL, &delim);

//     if (token != NULL) {
//       out += ", ";
//     }
//   }
//   free(dup);

//   return out;
// }


long long recursiveFactorial(long long n) {
  if(n > 1)
    return n * recursiveFactorial(n - 1);
  else
    return 1;
}
