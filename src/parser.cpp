#include <stdio.h>
#include <stdexcept>
#include "parser.hpp"

bool parseValue(std::string str, value_t* val) {
    value_t v;
    try {
        v = std::stof(str);
    } catch (const std::invalid_argument& e) {
        return false;
    } catch (const std::out_of_range& e) {
        return false;
    }
    *val=v;
    return true;
}
bool parseOperator(std::string str, Operator* val) {
    Operator o;
    int type=0;
    for (std::string s : OPERATOR_NAMES) {
        if (str==s) {
            o.type=(OperatorType)type;
            *val=o;
            return true;
        }
        type++;
    }
    return false;
}

bool parseStringToExprStackItem(std::string block, ExprStackItem* outItem) {
    // printf("Got str '%s'\n",block.c_str());
    ExprStackItem item;
    if (parseValue(block,&item.value)) {
        item.type = EXPR_STACK_ITEM_VALUE;
        *outItem=item;
        return true;
    }
    if (parseOperator(block,&item.op)) {
        item.type = EXPR_STACK_ITEM_OPERATOR;
        *outItem=item;
        return true;
    }
    return false;
}

ExprStack parseStringToExprStack(std::string str) {
    ExprStack stack;
    std::string currentBlock("");
    for (int i=0;i<str.size();i++) {
        char c = str[i];
        if (c=='\n') continue;
        if (c==' ') {
            ExprStackItem item;
            bool success=parseStringToExprStackItem(currentBlock,&item);
            if (success) {
                stack.stack.push_back(item);
            }
            currentBlock="";
        } else {
            currentBlock.push_back(c);
        }
        // printf("char '%c' block='%s'\n",c,currentBlock.c_str());
    }
    ExprStackItem item;
    bool success=parseStringToExprStackItem(currentBlock,&item);
    if (success) {
        stack.stack.push_back(item);
    }
    return stack;
}

std::string ExprStackItem::toString() {
    if (this->type==EXPR_STACK_ITEM_VALUE)
        return std::to_string(this->value);
    if (this->type==EXPR_STACK_ITEM_VARIABLE)
        return this->varName;
    if (this->type==EXPR_STACK_ITEM_OPERATOR)
        return OPERATOR_NAMES[this->op.type];
}
