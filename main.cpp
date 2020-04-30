#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <set>
#include <string>

bool is_sign_number(const std::string &str, const size_t &i) {
  return (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '+' ||
         str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == 'e' ||
         str[i] == 'p' || str[i] == '(' || str[i] == ')';
}

bool is_three(const std::string &str, size_t &i) {
  if (str.size() - i >= 4) {
    std::string tmp = str.substr(i, 3);
    if ((tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "cot" ||
         tmp == "exp" || tmp == "sqr") &&
        str[i + 3] == '(') {
      i += 2;
      return true;
    } else
      return false;
  } else
    return false;
}

bool is_real(const std::string &str, const size_t &i) {
  if (str[i] == '.') {
    for (size_t j = i + 1; j < str.size(); ++j) {
      if (!(str[j] >= '0' && str[j] <= '9') && j == i + 1)
        return false;
      if (str[j] == ')' || str[j] == '*' || str[j] == '-' || str[j] == '+' ||
          str[j] == '/' || j == str.size() - 1)
        return true;
      if (!(str[j] >= '0' && str[j] <= '9'))
        return false;
    }
  }
  return false;
}

bool is_int(const std::string &str) {
  for (char c : str) {
    if (c == '.')
      return false;
  }
  return true;
}

bool is_correct_bracket(const std::string &str) {
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
              str[i - 1] == '/' || str[i - 1] == '^' || str[i - 1] == '(')) {
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
      if (i < str.size() - 1) {
        if (!(str[i + 1] == '-' || str[i + 1] == '+' || str[i + 1] == '*' ||
              str[i + 1] == '/' || str[i + 1] == '^' || str[i + 1] == ')'))
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

bool is_correct_operations(const std::string &str) {
  size_t size = str.size();
  if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' ||
      str[0] == '^')
    return false;
  if (str[size - 1] == '+' || str[size - 1] == '-' || str[size - 1] == '*' ||
      str[size - 1] == '/' || str[size - 1] == '^')
    return false;
  if (!((str[size - 1] >= '0' && str[size - 1] <= '9') ||
        (str[size - 1] == ')')))
    return false;
  for (size_t i = 1; i < str.size() - 1; ++i) {
    if (str[i] == '+' || str[i] == '-') {
      if (!((str[i - 1] == ')' || str[i - 1] == '(' ||
             (str[i - 1] >= '0' && str[i - 1] <= '9')) &&
            (str[i + 1] == '(' || (str[i + 1] >= '0' && str[i + 1] <= '9')))) {
        if (size - i >= 4) {
          std::string tmp = str.substr(i + 1, 3);
          if (!(tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "cot" ||
                tmp == "sqr" || tmp == "exp"))
            return false;
        } else
          return false;
      }
    }
    if (str[i] == '*' || str[i] == '/' || str[i] == '^') {
      if (!((str[i - 1] == ')' || (str[i - 1] >= '0' && str[i - 1] <= '9')) &&
            (str[i + 1] == '(' || (str[i + 1] >= '0' && str[i + 1] <= '9')))) {
        if (size - i >= 4) {
          std::string tmp = str.substr(i + 1, 3);
          if (!(tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "cot" ||
                tmp == "sqr" || tmp == "exp"))
            return false;
        } else
          return false;
      }
    }
  }
  return true;
}

bool is_normal(const std::string &str) {
  size_t size = str.size();
  if (size == 0)
    return false;
  if (!(is_correct_bracket(str)))
    return false;
  if (!(is_correct_operations(str)))
    return false;
  if (size == 1) {
    return str[0] >= '0' && str[0] <= '9';
  }
  if (size == 2)
    return ((str[0] == '+' || str[0] == '-') &&
            (str[1] >= '0' && str[1] <= '9')) ||
           ((str[0] >= '0' && str[0] <= '9') &&
            (str[1] >= '0' && str[1] <= '9'));
  if (size >= 3) {
    for (size_t i = 0; i < size; ++i) {
      if (!is_sign_number(str, i) && !(is_three(str, i) && !(is_real(str, i))))
        return false;
    }
    return true;
  }
}

int count_operations(const std::string &str) {
  int result = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
        str[i] == '^')
      ++result;
    else {
      if (str.size() - i >= 3) {
        std::string tmp = str.substr(i, 3);
        if (tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "cot" ||
            tmp == "sqr" || tmp == "exp")
          ++result;
      }
    }
  }
  return result;
}

std::set<std::string> get_var_set(const std::string &str) {
  std::set<std::string> result;
  for (size_t i = 0; i < str.size(); ++i) {
    std::string var;
    size_t v_begin = 0, v_end = 0;
    if (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' &&
        str[i] != '^' && str[i] != 'p' && str[i] != 'e' &&
        !(str[i] >= '0' && str[i] <= '9')) {
      var = str.substr(i, 1);
      v_begin = i;
      for (size_t j = i + 1; j < str.size(); ++j) {
        if (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' &&
            str[i] != '^' && str[i] != 'p' && str[i] != 'e' &&
            !(str[i] >= '0' && str[i] <= '9')) {
          var += str[j];
          v_end = j;
        } else
          break;
      }
    }
    if (var != "sin" && var != "cos" && var != "tan" && var != "cot" &&
        var != "sqr" && var != "exp" &&
        (v_begin == 0 ||
         (str.at(v_begin - 1) == '+' || str.at(v_begin - 1) == '-' ||
          str.at(v_begin - 1) == '*' || str.at(v_begin - 1) == '/' ||
          str.at(v_begin - 1) == '^')))
      result.insert(var);
  }
  return result;
}

int main() {
  std::string str = "10+5+tan(10)^(cos(5))-(10)+x";
  std::cout << is_normal(str);
  return 0;
}
