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