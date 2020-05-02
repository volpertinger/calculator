#ifndef CALCULATOR_SOLVER_H
#define CALCULATOR_SOLVER_H

#include "solver.cpp"
#include "solver.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <set>
#include <string>

bool is_number(const std::string &str, const int &i);

bool is_simple_operation(const std::string &str, const int &i);

bool is_sign_number(const std::string &str, const int &i);

bool is_three(const std::string &str, int &i);

bool is_real(const std::string &str, const int &i);

bool is_available_name(const std::string &str);

bool is_correct_bracket(const std::string &str);

bool is_unar(const std::string &str, int i);

bool is_correct_operations(const std::string &str);

bool is_normal(const std::string &str);

bool is_functional_bracket(const std::string &str, int pos);

bool is_valid_arg_tan(double value);

bool is_valid_arg_cot(double value);

int count_operations(const std::string &str, const int &pos);

std::set<std::string> get_var_set(const std::string &str);

void setup_consts(std::string &str);

void setup_vars(std::string &str);

int find_end_trig(const std::string &str, int pos);

int find_end_num(const std::string &str, int pos);

int find_high_priority(const std::string &str);

double get_number(const std::string &str, int &pos);

void delete_brackets(std::string &str, const int &pos_init);

std::string get_operation(const std::string &str, int &pos);

void solve_simple(std::string &str, const int &pos_init);

void solve_simple_bracket(std::string &str, int &pos);

void solve(std::string &str);

#endif // CALCULATOR_SOLVER_H
