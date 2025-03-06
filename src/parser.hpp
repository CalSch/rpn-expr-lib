#pragma once
#include "expr.hpp"
#include "operators.hpp"

enum ExprStackItemType {
    EXPR_STACK_ITEM_VALUE,
    EXPR_STACK_ITEM_VARIABLE,
    EXPR_STACK_ITEM_OPERATOR,
};

struct ExprStackItem {
    ExprStackItemType type;
    value_t value;
    std::string varName;
    Operator op;

    std::string toString();
};
struct ExprStack {
    std::vector<ExprStackItem> stack;

};

bool parseValue(std::string str, value_t* val);
bool parseOperator(std::string str, Operator* op);

bool parseStringToExprStackItem(std::string block, ExprStackItem* outItem);
ExprStack parseStringToExprStack(std::string str);
Expr convertExprStackToExpr(ExprStack stack);
