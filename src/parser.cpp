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

Expr convertExprStackToExpr(ExprStack stack) {
    std::vector<Expr> exprStack; // bad name i know

    for (int i=0;i<stack.stack.size();i++) {
        ExprStackItem item = stack.stack[i];
        if (item.type==EXPR_STACK_ITEM_OPERATOR) {
            // Get the arguments
            int args=OPERATOR_ARGS[item.op.type];
            // Make a slice getting the last <args> items off the stack
            std::vector<Expr> argsVec=std::vector<Expr>(exprStack.end() - args, exprStack.end());
            // Construct the new expression
            Expr ex;
            ex.arguments=argsVec;
            ex.op=item.op;
            // Now remove the arguments from the stack
            for (int j=0;j<args;j++)
                exprStack.pop_back();
            // Now put the new expression on the stack
            exprStack.push_back(ex);
            // printf("I found an op '%s'\n",OPERATOR_NAMES[item.op.type].c_str());
            // printf("I just popped %d args, heres one '%s'\n",args,ex.arguments[0].toString().c_str());
            // printf("New expr: %s\n",ex.toString().c_str());
        } else {
            Expr ex;
            if (item.type==EXPR_STACK_ITEM_VALUE) {
                ex.is_value=true;
                ex.value=item.value;
            }
            if (item.type==EXPR_STACK_ITEM_VARIABLE) {
                ex.is_var=true;
                ex.varName=item.varName;
            }
            exprStack.push_back(ex);
        }
        // printf("heres the stack: ");
        // for (Expr e : exprStack) {
        //     printf("%s | ",e.toString().c_str());
        // }
        // printf("\n");
    }
    
    // TODO: assert that len(exprStack)==1
    return exprStack[0];
}