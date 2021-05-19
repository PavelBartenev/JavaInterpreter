#pragma once

#include "BaseSymbol.h"
#include "VarSymbol.h"
#include "../ast.hh"
#include "Scopes.h"
#include <vector>
#include <string>

class MethodSymbol : public BaseSymbol {
public:
    MethodSymbol(const std::string& ret_type, std::vector<VarSymbol*>& parameters, const std::string& name,
                 BaseScope* parent_scope, BaseScope* own_scope)
            : ret_type(ret_type), name(name), parent_scope(parent_scope), own_scope(own_scope), params(parameters) {
    }

    std::string ret_type;
    std::vector<VarSymbol*> params;
    std::string name;
    BaseScope* parent_scope;
    BaseScope* own_scope;
};
