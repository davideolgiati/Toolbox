// Copyright 2018 Davide Olgiati

#include "Include/math.h"

bool sum(const std::string input, std::string * const output) {
  if ("" == input) {
    *output = "0";
    return true;
  }

  std::vector<long double> numbers;
  const int size = MakeNumArray(input, &numbers);
  bool ret = false;
  *output = "null";

  if (size >= 0) {
      long double out = 0;
      for (auto number : numbers)
          out += number;
      *output = format(out);
      ret = true;
  }

  return ret;
}

bool mul(const std::string input, std::string * const output) {
  if ("" == input) {
    * output = "1";
    return true;
  }

  std::vector<long double> numbers;
  const int size = MakeNumArray(input, &numbers);
  bool ret = false;
  *output = "null";

  if (0 <= size) {
    long double out = 1;
    for (auto number : numbers)
        out *= number;
    *output = format(out);
  }

  return ret;
}

bool divide(const std::string input, std::string * const output) {
  if ("" == input) {
    * output = "1";
    return true;
  }

  std::vector<long double> numbers;
  const int size = MakeNumArray(input, &numbers);
  bool ret = false;
  *output = "null";

  if (0 <= size) {
    long double out = 0;

    for (auto number : numbers) {
      if (0 == std::fabs(out))
        out = number;
      else
        out /= number;
    }

    *output = format(out);
    ret = true;
  }
  return ret;
}

bool squareroot(const std::string input, std::string * const output) {
  if ("" == input) {
    * output = "1";
    return true;
  }

  std::vector<long double> numbers;
  const int size = MakeNumArray(input, &numbers);
  bool ret = false;
  *output = "null";

  if (0 <= size) {
    *output = "";

    for (auto number : numbers){
      if ("" != *output)
        * output += ", ";
      if (0 == number)
        * output += std::to_string(number);
      else if (0 < number)
        * output += format(sqrt(number));
    }
    *output += "\n";
    ret = true;
  }

  return ret;
}

bool logarithm(const std::string input, std::string * const output) {
  if ("" == input) {
    * output = "1";
    return true;
  }

  std::vector<long double> numbers;
  const int size = MakeNumArray(input, &numbers);
  bool ret = false;
  *output = "null";

  if (0 <= size) {
      *output = "";
      for (auto number : numbers){
          if ("" != *output)
              * output += ", ";

          if (0 == number)
                * output += std::to_string(number);
          else if (0 < number)
                * output += format(log(number));

          *output += "\n";
      }
      ret = true;
  }

  return ret;
}

bool binomial(const std::string input, std::string * const output) {
  if ("" == input) {
    return false;
  }

  std::vector<long double> numbers;
  const int size = MakeNumArray(input, &numbers);
  bool ret = false;
  *output = "null";

  if (size == 2 && numbers[0] >= numbers[1]) {
    long double out = 0;

    long double temp1 = numbers[0] - numbers[1];
    long double final1 = 1;
    long double final2 = (long double) Factorial((long long) numbers[1]);

    for(long double i = temp1 + 1; i <= numbers[0]; i += 1)
      final1 *= i;

    out = final1 / final2;

    *output = format(out);
    ret = true;
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


long long Factorial(long long n) {
  long long ret = 1;

  while (n > 1) {
    ret *= n;
    n--;
  }

  return ret;
}


bool FactorialHandler(const std::string input, std::string * const output) {
  if ("" == input) {
    return false;
  }

  std::vector<long double> numbers;
  const int size = MakeNumArray(input, &numbers);
  bool ret = false;
  long long last = 1;
  *output = "null";

  if (size >= 1) {
    *output = "";
    for(int x = 0; x < size; x++) {

      if (x > 0 && numbers[x] == numbers[x-1] + 1) {
        last *= (long long) numbers[x];
      } else if (x > 0 && numbers[x] == numbers[x-1] - 1) {
        last /= (long long) numbers[x - 1];
      } else {
        last = Factorial((long long) numbers[x]);
      }

      *output += format(last);

      if(x + 1 != size)
        *output += ", ";
    }
    ret = true;
  }

  return ret;
}
