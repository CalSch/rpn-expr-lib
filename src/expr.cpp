#include "expr.hpp"
#include "operators.hpp"

std::string Expr::toString() {
    if (this->is_value) {
        return std::to_string(this->value);
    }
    // return this->left->toString() + " " + this->right->toString() + " " + OPERATOR_NAMES[this->op.type];
    std::string str;
    for (Expr e : this->arguments) {
        str.append(e.toString());
        str.append(" ");
    }
    str.append(OPERATOR_NAMES[this->op.type]);
    return str;
}
std::string Expr::toTreeString(int level) {
    std::string prefix;
    for (int i=0;i<level;i++)
        prefix+="  ";
    if (this->is_value) {
        return prefix + std::string("Value: ") + std::to_string(this->value);
    }
    // return this->left->toString() + " " + this->right->toString() + " " + OPERATOR_NAMES[this->op.type];
    std::string str;
    str += prefix;
    str += OPERATOR_NAMES[this->op.type];
    str += ":\n";
    for (Expr e : this->arguments) {
        str.append(e.toTreeString(level+1));
        str.append("\n");
    }
    return str;
}


value_t evalOperator(Operator op, std::vector<value_t> args) {
    // printf("eval op %d\n",op.type);
    OperatorFuncPtr opFunc = OPERATOR_FUNCS[op.type];
    return opFunc(args);
}
