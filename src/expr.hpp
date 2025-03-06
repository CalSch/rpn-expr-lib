#pragma once
#include <vector>
#include <string>
#include "operators.hpp"

typedef float value_t;

enum OperatorType {
    OP_NONE,
    OP_ADD,
    OP_SUB,
    OP_MULT,
    OP_DIV,
};

struct Operator {
    OperatorType type;
};



value_t evalOperator(Operator op, std::vector<value_t> args);


struct Expr {
    bool is_value=false;
    value_t value;
    bool is_var=false;
    std::string varName;

    // Unused if is_value==true
    // Expr* left; // Use pointers bc otherwise an Expr would take up infinite space
    // Expr* right;
    std::vector<Expr> arguments;
    Operator op;

    std::string toString();
    std::string toTreeString(int level);
};
