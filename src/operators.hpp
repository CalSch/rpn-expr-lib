#pragma once
#include "expr.hpp"

typedef float value_t;

typedef value_t(*OperatorFuncPtr)(std::vector<value_t>);
const std::string OPERATOR_NAMES[]={
    "?",
    "+","-","*","/"
};

// Number of arguments an operator uses
const int OPERATOR_ARGS[]={
    -1,
    2,2,2,2
};
extern OperatorFuncPtr OPERATOR_FUNCS[5];

// Loads operator funcs from operators.hpp into `OPERATOR_FUNCS`
void loadOperatorFuncs();

value_t _operatorAdd(std::vector<value_t> args);
value_t _operatorSub(std::vector<value_t> args);
value_t _operatorMult(std::vector<value_t> args);
value_t _operatorDiv(std::vector<value_t> args);
