#include "eval.hpp"

value_t evalExpr(Expr ex, std::map<std::string,value_t> vars) {
    if (ex.is_var) {
        // Find the variable in `vars`
        bool found_var=false;
        value_t val;
        for (const auto& [name, value] : vars) { // why is c++ like this
            if (name==ex.varName) {
                found_var=true;
                val=value;
                break;
            }
        }
        //TODO: assert that found_var==true
        // Make it a value
        ex.is_value=true;
        ex.is_var=false;
        ex.value=val;
    }
    if (ex.is_value) {
        return ex.value;
    }

    // Now we know that it's an expression
    // We need a list of values to give to `evalOperator()`
    std::vector<value_t> values;
    for (Expr arg : ex.arguments) {
        values.push_back(evalExpr(arg, vars)); //TODO: maybe limit recursion
    }
    // We made the list! Now evaluate it
    value_t result = evalOperator(ex.op,values);

    // And we're done
    return result;
}
