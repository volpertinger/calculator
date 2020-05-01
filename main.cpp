#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <set>
#include <string>

bool is_number(const std::string &str, const size_t &i) {
  if (i >= 0 && i < str.size()) {
    return ((str[i] >= '0' && str[i] <= '9') || str[i] == '.');
  }
  return false;
}

bool is_simple_operation(const std::string &str, const size_t &i) {
  if (i >= 0 && i < str.size()) {
    return (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
            str[i] == '^');
  }
  return false;
}

bool is_sign_number(const std::string &str, const size_t &i) {
  if (i >= 0 && i < str.size()) {
    return (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '+' ||
           str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == 'e' ||
           str[i] == 'p' || str[i] == '(' || str[i] == ')';
  }
  return false;
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

bool is_available_name(const std::string &str) {
  return str != "sin" && str != "cos" && str != "tan" && str != "cot" &&
         str != "sqr" && str != "exp" && str != "e" && str != "p";
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
    if (!is_sign_number(str, i)) {
      var = str.substr(i, 1);
      v_begin = i;
      v_end = i;
      for (size_t j = i + 1; j < str.size(); ++j) {
        if (!is_sign_number(str, j)) {
          var += str[j];
          v_end = j;
        } else
          break;
      }
    }
    if (is_available_name(var) &&
        (v_begin == 0 || is_sign_number(str, v_begin - 1)) &&
        (v_end == str.size() - 1 || is_sign_number(str, v_end + 1))) {
      result.insert(var);
      i = v_end + 1;
    }
  }
  return result;
}

void setup_vars(std::string &str) {
  std::set<std::string> list = get_var_set(str);
  list.erase("");
  for (const auto &var : list) {
    std::string val;
    size_t pos = 0;
    std::cout << "enter value of " << var << std::endl;
    std::cin >> val;
    while (str.find(var, pos) != -1) {
      pos = str.find(var, pos);
      if ((is_sign_number(str, pos - 1) || pos == 0) &&
          (is_sign_number(str, pos + var.size()) ||
           pos + var.size() == str.size()))
        str.replace(pos, var.size(), val);
      ++pos;
    }
  }
}

double get_number(const std::string &str, int &pos) {
  std::string result;
  for (size_t i = pos; i < str.size(); ++i) {
    if ((is_number(str, i) || str[i] == '(' || str[i] == ')') ||
        ((str[i] == '+' || str[i] == '-') && (!is_number(str, i - 1))))
      result += str[i];
    else
      break;
  }
  pos += result.size();
  if (result[0] == '(')
    result = result.substr(1, result.size() - 1);
  if (result[result.size() - 1] == ')')
    result = result.substr(0, result.size() - 1);
  return stod(result);
}

std::string get_operation(const std::string &str, int &pos) {
  std::string result;
  for (size_t i = pos; pos < str.size(); ++i) {
    if (is_simple_operation(str, i)) {
      result = str.substr(i, 1);
      ++pos;
      return result;
    }
    if (is_three(str, i)) {
      result = str.substr(i - 2, 3);
      pos += 3;
      return result;
    }
  }
  return result;
}

void solve_simple_operation(std::string &str, const int &pos) {
  int pos_end = pos;
  double lhs = 0, rhs = 0;
  if (is_number(str, pos_end) || str[pos_end] == '(' || str[pos_end] == ')')
    lhs = get_number(str, pos_end);
  std::string operation = get_operation(str, pos_end);
  if (is_number(str, pos_end) || str[pos_end] == '(' || str[pos_end] == ')')
    rhs = get_number(str, pos_end);
  if (operation == "+") {
    double result = lhs + rhs;
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "-") {
    double result = lhs - rhs;
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "*") {
    double result = lhs * rhs;
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "/") {
    if (rhs == 0) {
      std::cout << "divison by zero" << std::endl;
      return;
    }
    double result = lhs / rhs;
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "^") {
    double result = pow(lhs, rhs);
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "sin") {
    double result = sin(rhs);
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "cos") {
    double result = cos(rhs);
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }

  if (operation == "tan") {
    double result = tan(rhs);
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }

  if (operation == "cot") {
    double result = 1 / tan(rhs);
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }

  if (operation == "sqr") {
    double result = sqrt(rhs);
    std::string result_str = std::to_string(result);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }

  if (operation == "exp") {
    if (rhs >= 0) {
      double result = exp(rhs);
      std::string result_str = std::to_string(result);
      str.replace(pos, pos_end - pos, result_str);
    } else {
      std::cout << "wrong exp arg" << std::endl;
      return;
    }
    return;
  }
}

void solve_simple_bracket(std::string &str) {}

int main() {
  std::string str = "exp(+1)";
  int i = 0;
  std::cout << is_normal(str) << std::endl;
  solve_simple_operation(str, i);
  std::cout << str;
  return 0;
}
