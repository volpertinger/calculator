#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <set>
#include <string>

bool is_number(const std::string &str, const int &i) {
  if (i >= 0 && i < str.size()) {
    return ((str[i] >= '0' && str[i] <= '9') || str[i] == '.');
  }
  return false;
}

bool is_simple_operation(const std::string &str, const int &i) {
  if (i >= 0 && i < str.size()) {
    return (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
            str[i] == '^');
  }
  return false;
}

bool is_sign_number(const std::string &str, const int &i) {
  if (i >= 0 && i < str.size()) {
    return ((str[i] >= '0' && str[i] <= '9') || str[i] == '-' ||
            str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '^' ||
            str[i] == '(' || str[i] == ')' || str[i] == '.');
  }
  return false;
}

bool is_three(const std::string &str, int &i) {
  if (str.size() - i >= 4) {
    std::string tmp = str.substr(i, 3);
    if ((tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "cot" ||
         tmp == "exp" || tmp == "sqr") &&
        str[i + 3] == '(') {
      i += 3;
      return true;
    } else
      return false;
  } else
    return false;
}

bool is_real(const std::string &str, const int &i) {
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
    for (int i = 0; i < size; ++i) {
      if (!is_sign_number(str, i) && !(is_three(str, i) && !(is_real(str, i))))
        return false;
    }
    return true;
  }
}

bool is_functional_bracket(const std::string &str, int pos) {
  int tmp = pos - 3;
  if (tmp >= 0) {
    if (is_three(str, tmp))
      return true;
  }
  return false;
}

bool is_valid_arg_tan(double value) {
  if (value >= 0) {
    for (; value >= 3.14159265; value -= 3.14159265)
      ;
    return (value - 3.14159262 / 2 > 0.0001 ||
            value - 3.14159262 / 2 < -0.0001);
  }

  if (value < 0) {
    for (; value <= 0; value += 3.14159265)
      ;
    return (value - 3.14159262 / 2 > 0.0001 ||
            value - 3.14159262 / 2 < -0.0001);
  }
}

bool is_valid_arg_cot(double value) {
  if (value >= 0) {
    for (; value > 3.14159265; value -= 3.14159265)
      ;
    return (value - 3.14159262 > 0.0001 || value - 3.14159262 < -0.0001) &&
           (value > 0.0001 || value < -0.0001);
  }

  if (value < 0) {
    for (; value >= 0; value += 3.14159265)
      ;
    return (value - 3.14159262 > 0.0001 || value - 3.14159262 < -0.0001);
  }
}

bool is_unar(const std::string &str, int i) {
  if (i == 0 && str[i] == '-')
    return true;
  return !is_number(str, i - 1);
}

int count_operations(const std::string &str, const int &pos) {
  int result = 0;
  for (size_t i = pos; i < str.size() && str[i] != ')'; ++i) {
    if (str[i] == '+' || (str[i] == '-' && !is_unar(str, i)) || str[i] == '*' ||
        str[i] == '/' || str[i] == '^')
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
        (v_end == str.size() - 1 || is_sign_number(str, v_end + 1)) &&
        !var.empty()) {
      result.insert(var);
      i = v_end + 1;
    }
  }
  return result;
}

void setup_consts(std::string &str) {
  std::set<std::string> list;
  list.emplace("e");
  list.emplace("p");
  for (const auto &var : list) {
    std::string val;
    size_t pos = 0;
    if (var == "e")
      val = "2.71828182846";
    if (var == "p")
      val = "3.14159265358";
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

void setup_vars(std::string &str) {
  setup_consts(str);
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

int find_end_trig(const std::string &str, int pos) {
  int level = 0;
  for (; str[pos] != '('; ++pos)
    ;
  ++pos;
  ++level;
  for (; level != 0; ++pos) {
    if (str[pos] == '(')
      ++level;
    if (str[pos] == ')')
      --level;
  }
  return pos;
}

int find_end_num(const std::string &str, int pos) {
  if (str[pos] == '-')
    ++pos;
  for (; !is_simple_operation(str, pos); ++pos)
    ;
  ++pos;
  for (; is_number(str, pos); ++pos)
    ;
  return pos;
}

int find_high_priority(const std::string &str) {
  int max_level = 0, level = 0, result = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      ++level;
      if (level > max_level && count_operations(str, i) > 0)
        result = i;
    }
    if (str[i] == ')')
      --level;
  }
  return result;
}

double get_number(const std::string &str, int &pos) {
  std::string result;
  if (pos > 0) {
    if (is_unar(str, pos - 1) && str[pos - 1] == '-') {
      result = '-';
      ++pos;
    }
  }
  for (int i = pos; i < str.size(); ++i) {
    if ((is_number(str, i) || str[i] == '(' || str[i] == ')') ||
        ((str[i] == '+' || str[i] == '-') && (!is_number(str, i - 1))))
      result += str[i];
    else
      break;
  }
  pos += result.size();
  if (result[0] == '-')
    --pos;
  if (result[0] == '(')
    result = result.substr(1, result.size() - 1);
  if (result[result.size() - 1] == ')')
    result = result.substr(0, result.size() - 1);
  return stod(result);
}

void delete_brackets(std::string &str, const int &pos_init) {
  int pos = pos_init;
  if (str[pos] == '(') {
    str.erase(pos, 1);
    for (int i = pos; i < str.size(); ++i) {
      if (str[i] == ')') {
        str.erase(i, 1);
        break;
      }
    }
  }
}

std::string get_operation(const std::string &str, int &pos) {
  std::string result;
  for (int i = pos; pos < str.size(); ++i) {
    if (is_simple_operation(str, i) && !is_unar(str, i)) {
      result = str.substr(i, 1);
      ++pos;
      return result;
    }
    if (is_three(str, i)) {
      result = str.substr(i - 3, 3);
      pos += 3;
      return result;
    }
  }
  return result;
}

void solve_simple(std::string &str, const int &pos) {
  int pos_end = pos;
  double lhs = 0, rhs = 0;
  if (is_number(str, pos_end) || str[pos_end] == '(' || str[pos_end] == ')' ||
      (is_unar(str, pos_end) && str[pos_end] == '-'))
    lhs = get_number(str, pos_end);
  std::string operation = get_operation(str, pos_end);
  if (is_number(str, pos_end) || str[pos_end] == '(' || str[pos_end] == ')' ||
      (is_unar(str, pos_end) && str[pos_end] == '-'))
    rhs = get_number(str, pos_end);
  if (operation == "*") {
    double result = lhs * rhs;
    std::string result_str = std::to_string(result);
    pos_end = find_end_num(str, pos);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "/") {
    if (rhs < 0.0001 && rhs > -0.0001) {
      std::cout << "divison by zero" << std::endl;
      return;
    }
    double result = lhs / rhs;
    std::string result_str = std::to_string(result);
    pos_end = find_end_num(str, pos);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "^") {
    double result = pow(lhs, rhs);
    std::string result_str = std::to_string(result);
    pos_end = find_end_num(str, pos);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "+") {
    double result = lhs + rhs;
    std::string result_str = std::to_string(result);
    pos_end = find_end_num(str, pos);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "-") {
    double result = lhs - rhs;
    std::string result_str = std::to_string(result);
    pos_end = find_end_num(str, pos);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "sin") {
    double result = sin(rhs);
    std::string result_str = std::to_string(result);
    pos_end = find_end_trig(str, pos);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }
  if (operation == "cos") {
    double result = cos(rhs);
    std::string result_str = std::to_string(result);
    pos_end = find_end_trig(str, pos);
    str.replace(pos, pos_end - pos, result_str);
    return;
  }

  if (operation == "tan") {
    if (is_valid_arg_tan(rhs)) {
      double result = tan(rhs);
      std::string result_str = std::to_string(result);
      pos_end = find_end_trig(str, pos);
      str.replace(pos, pos_end - pos, result_str);
      return;
    } else {
      std::cout << "sin/0" << std::endl;
      return;
    }
  }

  if (operation == "cot") {
    if (is_valid_arg_cot(rhs)) {
      double result = 1 / tan(rhs);
      std::string result_str = std::to_string(result);
      pos_end = find_end_trig(str, pos);
      str.replace(pos, pos_end - pos, result_str);
      return;
    } else {
      std::cout << "cos/0" << std::endl;
      return;
    }
  }

  if (operation == "sqr") {
    if (rhs >= 0) {
      double result = sqrt(rhs);
      std::string result_str = std::to_string(result);
      pos_end = find_end_trig(str, pos);
      str.replace(pos, pos_end - pos, result_str);
      return;
    } else {
      std::cout << "<0 in sqr" << std::endl;
    }
  }

  if (operation == "exp") {
    if (rhs >= 0) {
      double result = exp(rhs);
      std::string result_str = std::to_string(result);
      pos_end = find_end_trig(str, pos);
      str.replace(pos, pos_end - pos, result_str);
    } else {
      std::cout << "wrong exp arg" << std::endl;
      return;
    }
    return;
  }
}

void solve_simple_bracket(std::string &str, int &pos) {
  int begin = pos;
  for (int i = pos; str[i] != ')' && i < str.size(); ++i) {
    if (is_three(str, i)) {
      solve_simple(str, i - 3);
      i = pos;
    }
  }
  for (int i = pos; str[i] != ')' && i < str.size(); ++i) {
    if (str[i] == '*' || str[i] == '/' || str[i] == '^') {
      for (begin = i - 1; is_number(str, begin); --begin)
        ;
      solve_simple(str, begin + 1);
      i = pos;
    }
  }
  for (int i = pos; str[i] != ')' && i < str.size(); ++i) {
    if (str[i] == '+' || (str[i] == '-' && !is_unar(str, i))) {
      for (begin = i - 1; is_number(str, begin); --begin)
        ;
      solve_simple(str, begin + 1);
      i = pos;
    }
  }
  if (!is_functional_bracket(str, pos))
    delete_brackets(str, pos);
}

void solve(std::string &str) {
  setup_vars(str);
  if (is_normal(str)) {
    while (int pos = find_high_priority(str)) {
      solve_simple_bracket(str, pos);
    }
    int pos = 0;
    solve_simple_bracket(str, pos);
  } else
    std::cout << "bad string" << std::endl;
}

int main() {
  std::string str = "cot(0)", str_tmp = "-30";
  solve(str);
  std::cout << str;
  return 0;
}
