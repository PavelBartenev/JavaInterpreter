#pragma once
#include <variant>
#include <string>

using SomeType = std::variant<int, bool, std::string>;

enum struct op_id {
    AND,
    OR,
    LESS,
    GREATER,
    EQUAL,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PERCENT
};

enum struct type_id {
    INT,
    BOOL,
    VOID,
    ID,
    STRING,
    OTHER
};