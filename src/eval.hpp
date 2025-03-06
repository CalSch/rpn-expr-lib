#pragma once
#include <map>
#include "expr.hpp"
#include "operators.hpp"

value_t evalExpr(Expr ex, std::map<std::string,value_t> vars);

