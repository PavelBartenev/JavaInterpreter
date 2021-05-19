#pragma once

#include "BaseSymbol.h"
#include "Scopes.h"
#include <string>

class VarSymbol : public BaseSymbol {
public:
     VarSymbol(const std::string& name, const std::string& type, BaseScope* scope = nullptr)
    : name(name), type(type), parent_scope(scope) {}

    std::string type;
    std::string name;
    BaseScope* parent_scope;
};
