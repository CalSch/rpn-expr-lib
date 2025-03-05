#pragma once
#include <vector>
#include <string>

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

typedef value_t (*OperatorFuncPtr)(std::vector<value_t>);
const std::string OPERATOR_NAMES[]={
    "?",
    "+","-","*","/"
};
extern OperatorFuncPtr OPERATOR_FUNCS[5];

// Loads operator funcs from operators.hpp into `OPERATOR_FUNCS`
void loadOperatorFuncs();

value_t evalOperator(Operator op, std::vector<value_t> args);


struct Expr {
    bool is_value;
    value_t value;

    // Unused if is_value==true
    // Expr* left; // Use pointers bc otherwise an Expr would take up infinite space
    // Expr* right;
    std::vector<Expr> arguments;
    Operator op;

    std::string toString();
};
