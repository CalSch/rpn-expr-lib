#include "operators.hpp"

value_t _operatorAdd(std::vector<value_t> args) {
    return args[0] + args[1];
}
value_t _operatorSub(std::vector<value_t> args) {
    return args[0] - args[1];
}
value_t _operatorMult(std::vector<value_t> args) {
    return args[0] * args[1];
}
value_t _operatorDiv(std::vector<value_t> args) {
    return args[0] / args[1];
}

OperatorFuncPtr OPERATOR_FUNCS[5];
void loadOperatorFuncs() {
    OPERATOR_FUNCS[OP_ADD] = *_operatorAdd;
    OPERATOR_FUNCS[OP_SUB] = *_operatorSub;
    OPERATOR_FUNCS[OP_MULT] = *_operatorMult;
    OPERATOR_FUNCS[OP_DIV] = *_operatorDiv;
}