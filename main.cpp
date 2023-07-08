#include <iostream>
#include <string>
#include <list>

int main() {
  std::list<double> numbers = {};

  do {
    std::string input;
    std::cout << "Enter RPN (or empty string to exit):\n> ";
    std::getline(std::cin, input);
    if (!input.length()) {
      break;
    }

    char *start = (char *)input.c_str();
    char *end = nullptr;

    do {
      double number = 0;

      std::cout << "Processing: " << start << std::endl;
      long long significant = strtoll(start, &end, 10);
      std::cout << "Got: " << significant << std::endl;

      number += significant;

      if (*end == '.') {
        std::cout << "Floating point detected!" << std::endl;

        end++;
        start = end;
        end = nullptr;
        std::cout << "Processing: " << start << std::endl;
        long long fractional = strtoll(start, &end, 10);
        std::cout << "Got: " << fractional << std::endl;

        number += fractional / pow(10, end - start);
        std::cout << "Floating point result: " << number << std::endl;
      }

      // did not read a number
      if (start == end) {
        // skip empty space
        while (*start) {
          if (*start == ' ') start++;
          else break;
        }

        // end of string
        if (!*start) {
          std::cout << "EOF" << std::endl;
          break;
        }

        if (*start == '+') {
          double a = numbers.back();
          numbers.pop_back();
          double b = numbers.back();
          numbers.pop_back();

          number = a + b;
          std::cout << "Sum: " << a << " + " << b << " = " << number << std::endl;

          start++;
        } else if (*start == '*') {
          double a = numbers.back();
          numbers.pop_back();
          double b = numbers.back();
          numbers.pop_back();

          number = a * b;
          std::cout << "Mult: " << a << " * " << b << " = " << number << std::endl;

          start++;
        } else if (*start == '-') {
          double a = numbers.back();
          numbers.pop_back();
          double b = numbers.back();
          numbers.pop_back();

          number = b - a;
          std::cout << "Sub: " << a << " - " << b << " = " << number << std::endl;

          start++;
        } else if (*start == '/') {
          double a = numbers.back();
          numbers.pop_back();
          double b = numbers.back();
          numbers.pop_back();

          number = b / a;
          std::cout << "Div: " << a << " / " << b << " = " << number << std::endl;

          start++;
        } else {
          std::cout << "Unknown operation! Bailing!" << std::endl;
          break;
        }

        end = start;
      }

      numbers.push_back(number);
      start = end;
      end = nullptr;
    } while (start != end);

    std::cout << "Result:";
    for (const auto& number : numbers) {
        std::cout << " " << number;
    }
    std::cout << std::endl;
  } while (true);

  return 0;
}
