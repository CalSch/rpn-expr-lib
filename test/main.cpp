#include <stdio.h>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include "parser.hpp"
#include "eval.hpp"

int main() {
    loadOperatorFuncs();
    std::map<std::string,value_t> vars;
    vars["ans"]=0;
    while (1) {
        struct timeval start, end;

        printf("expr> ");
        char buf[100];
        fgets(buf,99,stdin);
        gettimeofday(&start,0);
    
        std::string expr = std::string(buf);
    
        // printf("in: '%s'\n",buf);
        // printf("str: '%s'\n",expr.c_str());
    
        ExprStack stack=parseStringToExprStack(expr);
        std::vector<value_t> evalStack;
        Expr ex = convertExprStackToExpr(stack);
        // printf("%s\n",ex.toTreeString(0).c_str());
        value_t result = evalExpr(ex, vars);
        printf("result: %f\n",result);

        vars["ans"]=result;
        
        gettimeofday(&end,0);
        
        printf("took %fms\n",float(end.tv_usec-start.tv_usec)/1000.0f);
    }

    return 0;
}