#include "expr.hpp"
#include "operators.hpp"

std::string Expr::toString() {
    if (this->is_value) {
        return std::to_string(this->value);
    }
    return this->left->toString() + " " + this->right->toString() + " " + OPERATOR_NAMES[this->op.type];
}

OperatorFuncPtr OPERATOR_FUNCS[5];
void loadOperatorFuncs() {
    OPERATOR_FUNCS[OP_ADD] = *_operatorAdd;
    OPERATOR_FUNCS[OP_SUB] = *_operatorSub;
    OPERATOR_FUNCS[OP_MULT] = *_operatorMult;
    OPERATOR_FUNCS[OP_DIV] = *_operatorDiv;
}

value_t evalOperator(Operator op, value_t left, value_t right) {
    // printf("eval op %d\n",op.type);
    OperatorFuncPtr opFunc = OPERATOR_FUNCS[op.type];
    return opFunc(left,right);
}
