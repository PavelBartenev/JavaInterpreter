#pragma once

#include "BaseSymbol.h"
#include <unordered_map>
#include <vector>

class BaseScope {
public:
    std::unordered_map<std::string, BaseSymbol*> elements;
    BaseScope* parent = nullptr;
};