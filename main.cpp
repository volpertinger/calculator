#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>

size_t find_left(const std::string &str) {
  int result = 0;
  for (char c : str) {
    if (c == '(')
      ++result;
  }
  return result;
}

size_t find_right(const std::string &str) {
  int result = 0;
  for (char c : str) {
    if (c == '(')
      ++result;
  }
  return result;
}

void solve_bracket(const std::string &str) {}

bool is_int(const std::string &str) {
  for (char c : str) {
    if (c == '.')
      return false;
  }
  return true;
}

bool is_correct_scobes(const std::string &str) {
  int tmp = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (i < str.size() - 1) {
      if (str[i] == '(' && str[i + 1] == ')')
        return false;
    }
    if (str[i] == '(') {
      ++tmp;
      if (i > 1) {
        if (!(str[i - 1] == '-' || str[i - 1] == '+' || str[i - 1] == '*' ||
              str[i - 1] == '/')) {
          if (i >= 3) {
            std::string tmp_s = str.substr(i - 3, 3);
            if (tmp_s != "sin" && tmp_s != "cos" && tmp_s != "tan" &&
                tmp_s != "cot" && tmp_s != "exp" && tmp_s != "sqr")
              return false;
          } else
            return false;
        }
      } else {
        if (i != 0)
          return false;
      }
    }
    if (str[i] == ')') {
      --tmp;
      if (i < str.size() - 2) {
        if (!(str[i + 1] == '-' || str[i + 1] == '+' || str[i + 1] == '*' ||
              str[i + 1] == '/'))
          return false;
      } else {
        if (i != str.size() - 1)
          return false;
      }
    }
    if (tmp < 0)
      return false;
  }
  return tmp == 0;
}

bool is_normal(const std::string &str) {
  size_t size = str.size();
  if (size == 0)
    return false;
  if (!(is_correct_scobes(str)))
    return false;
  if (size == 1) {
    return str[0] >= '0' && str[0] <= '9';
  }
  if (size == 2)
    return (str[0] == '+' || str[0] == '-') && (str[1] >= '0' && str[1] <= '9');
  if (size >= 3) {
    for (size_t i = 0; i < size; ++i) {
      bool is_one = false, is_three = false, is_dot = false;
      if ((str[i] >= '0' && str[i] <= '9') ||
          (str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/' ||
           str[i] == 'x' || str[i] == 'e' || str[i] == 'p') ||
          str[i] == '(' || str[i] == ')')
        is_one = true;
      if (size - i >= 4) {
        std::string tmp = str.substr(i, 3);
        if ((tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "cot" ||
             tmp == "exp" || tmp == "sqrt") &&
            str[i + 3] == '(')
          is_three = true;
      }
      if (str[i] == '.') {
        for (size_t j = i + 1; j < size; ++j) {
          if (!(str[j] >= '0' && str[j] <= '9') && j == i + 1)
            return false;
          if (str[j] == ')' || str[j] == '*' || str[j] == '-' ||
              str[j] == '+' || str[j] == '/' || j == size - 1) {
            is_dot = true;
            break;
          }
          if (!(str[j] >= '0' && str[j] <= '9'))
            return false;
        }
      }
      if (str[i] == '(') {
      }
      if (!is_one && !is_three && !is_dot)
        return false;
    }
    return true;
  }
}

void solve_trigonometry(const std::string &str) {
  size_t size = str.size();
  if (str[0] == 's') {
    std::string tmp = str.substr(3, size - 1);
  }
}

int main() {
  std::cout << is_normal("+-");
  return 0;
}
