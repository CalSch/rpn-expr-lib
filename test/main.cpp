#include <stdio.h>
#include "parser.hpp"

int main() {
    loadOperatorFuncs();
    while (1) {

        printf("expr> ");
        char buf[100];
        fgets(buf,99,stdin);
    
        std::string expr = std::string(buf);
    
        // printf("in: '%s'\n",buf);
        // printf("str: '%s'\n",expr.c_str());
    
        ExprStack stack=parseStringToExprStack(expr);
        std::vector<value_t> evalStack;
        // printf("stack:\n");
        for (ExprStackItem item : stack.stack) {
            // printf("item: %s\n",item.toString().c_str());
            // printf("  evalstack: ");
            // for (value_t i:evalStack)
            //     printf("%f ",i);
            // printf("\n");
            if (item.type==EXPR_STACK_ITEM_VALUE)
                evalStack.push_back(item.value);
            if (item.type==EXPR_STACK_ITEM_OPERATOR) {
                value_t right = evalStack[evalStack.size()-1];
                evalStack.pop_back();
                value_t left = evalStack[evalStack.size()-1];
                evalStack.pop_back();
                value_t result = evalOperator(item.op,left,right);
                evalStack.push_back(result);
            }
            
        }
        printf("%f\n",evalStack[0]);
    }

    return 0;
}