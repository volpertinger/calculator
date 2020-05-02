#include "solver.h"
#include <iostream>
#include <string>

int main() {
  std::string str = "(1+4-10)*cos(0)";
  solve(str);
  std::cout << str << std::endl;
  return 0;
}
