#pragma once

#include "BaseSymbol.h"
#include "Scopes.h"


class ClassSymbol : public BaseSymbol {
public:
    ClassSymbol(const std::string& name, BaseScope* parent_scope, BaseScope* own_scope)
    : name(name), parent_scope(parent_scope), own_scope(own_scope) {}

    std::string name;
    BaseScope* parent_scope;
    BaseScope* own_scope;
};
