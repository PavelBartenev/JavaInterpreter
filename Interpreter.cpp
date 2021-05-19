#include "Interpreter.h"
#include "ast.hh"
#include <iostream>
#include <string>

void Interpreter::Visit(AST* ast) {
    ast->main->Accept(this);
}

void Interpreter::Visit(MainFunc *main) {
    main->block->Accept(this);
}

void Interpreter::Visit(ClassesBlock *classes) {
}
void Interpreter::Visit(Class *some_class) {
}
void Interpreter::Visit(ClassBody *class_body) {
}


void Interpreter::Visit(StatementsBlock *statements) {
    if (return_called) {
        return;
    }

    for (auto& stmt : statements->statements) {
        stmt->Accept(this);
        if (return_called) {
            return;
        }
    }
}

void Interpreter::Visit(IfStmt *if_stmt) {
    if_stmt->condition->Accept(this);

    if (!IsTosValueTrue()) {
        if (if_stmt->if_not) {
            if_stmt->if_not->Accept(this);
        }
    } else {
        if_stmt->then->Accept(this);
    }
}

void Interpreter::Visit(LitExpr *lit_expr) {
    SetTosValue(lit_expr->literal);
}

void Interpreter::Visit(NotExpr *not_expr) {
    not_expr->expr->Accept(this);

    if (!IsTosValueTrue()) {
        SetTosValue(true);
    } else {
        SetTosValue(false);
    }
}

void Interpreter::Visit(RetStmt *ret_stmt) {
    ret_stmt->code->Accept(this);
    return_called = true;
}

void Interpreter::SetTosValue(SomeType value) {
    tos_value = value;
}

int Interpreter::Interpret(AST *ast) {
    ast->Accept(this);

    if (std::get_if<int>(&tos_value)) {
        return *std::get_if<int>(&tos_value);
    } else {
        return 1;
    }
}

bool Interpreter::IsValueTrue(SomeType val) {
    return !(std::get_if<int>(&val) &&
             *std::get_if<int>(&val) == 0 ||
             std::get_if<bool>(&val) &&
             !*std::get_if<bool>(&val));
}

bool Interpreter::IsTosValueTrue() {
    return IsValueTrue(tos_value);
}

void Interpreter::Visit(PrintStmt *print) {
    print->expr->Accept(this);

    if (std::get_if<int>(&tos_value)) {
        std::cout << *std::get_if<int>(&tos_value);
    } else if (std::get_if<std::string>(&tos_value)) {
        std::cout << *std::get_if<std::string>(&tos_value);
    } else if (std::get_if<bool>(&tos_value)) {
        std::cout << *std::get_if<bool>(&tos_value); //////// STRINGS TO CONTAIN MORE DIFF CHARS
    }
}

void Interpreter::Visit(VarDecl<type_id::INT> *decl) {
    variables[decl->id] = 0;
}

void Interpreter::Visit(VarDecl<type_id::STRING> *decl) {
    variables[decl->id] = "0";

}

void Interpreter::Visit(VarDecl<type_id::BOOL> *decl) {
    variables[decl->id] = false;
}

void Interpreter::Visit(VarDecl<type_id::ID> *decl) {
    //TODO()
}

void Interpreter::Visit(VarDecl<type_id::VOID> *decl) {
    //TODO()
}

void Interpreter::Visit(IdExpr *id) {
    SetTosValue(variables[id->id]);
}

void Interpreter::Visit(Lvalue *val) {
    SetTosValue(val->id);
}

void Interpreter::Visit(AssignStmt *assign) {
    assign->code->Accept(this);
    SomeType assign_val = tos_value;

    assign->var->Accept(this);

    if (std::holds_alternative<std::string>(tos_value))
        variables[std::get<std::string>(tos_value)] = assign_val;
}

void Interpreter::Visit(BinExpr<op_id::PLUS>* plus_expr) {
    plus_expr->first->Accept(this);
    SomeType first = tos_value;

    plus_expr->second->Accept(this);

    SetTosValue(std::get<int>(first) + std::get<int>(tos_value));
}

void Interpreter::Visit(BinExpr<op_id::MINUS> *minus_expr) {
    minus_expr->first->Accept(this);
    SomeType first = tos_value;

    minus_expr->second->Accept(this);

    SetTosValue(std::get<int>(first) - std::get<int>(tos_value));
}

void Interpreter::Visit(BinExpr<op_id::STAR> *mul_expr) {
    mul_expr->first->Accept(this);
    SomeType first = tos_value;

    mul_expr->second->Accept(this);

    SetTosValue(std::get<int>(first) * std::get<int>(tos_value));

}

void Interpreter::Visit(BinExpr<op_id::SLASH> *div_expr) {
    div_expr->first->Accept(this);
    SomeType first = tos_value;

    div_expr->second->Accept(this);

    SetTosValue(std::get<int>(first) / std::get<int>(tos_value));

}

void Interpreter::Visit(BinExpr<op_id::EQUAL> *equal_expr) {
    equal_expr->first->Accept(this);
    SomeType first = tos_value;

    equal_expr->second->Accept(this);

    SetTosValue(first == tos_value);
}

void Interpreter::Visit(BinExpr<op_id::AND> *and_expr) {
    and_expr->first->Accept(this);
    SomeType first = tos_value;

    and_expr->second->Accept(this);   ///priorities!!!

    SetTosValue(IsValueTrue(first) && IsTosValueTrue());
}

void Interpreter::Visit(BinExpr<op_id::OR> *or_expr) {
    or_expr->first->Accept(this);
    SomeType first = tos_value;

    or_expr->second->Accept(this);

    SetTosValue(IsValueTrue(first) || IsTosValueTrue());
}

void Interpreter::Visit(BinExpr<op_id::LESS> *less_expr) {
    less_expr->first->Accept(this);
    SomeType first = tos_value;

    less_expr->second->Accept(this);

    if (std::holds_alternative<int>(first) && std::holds_alternative<int>(tos_value)) {
        SetTosValue(first < tos_value);
    } else {
        SetTosValue(false);
    }
}

void Interpreter::Visit(BinExpr<op_id::GREATER> *greater_expr) {
    greater_expr->first->Accept(this);
    SomeType first = tos_value;

    greater_expr->second->Accept(this);

    if (std::holds_alternative<int>(first) && std::holds_alternative<int>(tos_value)) {
        SetTosValue(first > tos_value);
    } else {
        SetTosValue(false);
    }
}

void Interpreter::Visit(BinExpr<op_id::PERCENT> *percent_expr) {
    percent_expr->first->Accept(this);
    SomeType first = tos_value;

    percent_expr->second->Accept(this);

    if (std::holds_alternative<int>(first) && std::holds_alternative<int>(tos_value)) {
        SetTosValue(first < tos_value);
    } else {
        SetTosValue(false);
    }
}

void Interpreter::Visit(WhileStmt *while_stmt) {
    while_stmt->condition->Accept(this);

    while (IsTosValueTrue()) {
        while_stmt->code->Accept(this);
        while_stmt->condition->Accept(this);
    }
}

void Interpreter::Visit(FuncDecl<type_id::VOID> *decl) {
}
void Interpreter::Visit(FuncDecl<type_id::ID> *decl) {
}
void Interpreter::Visit(FuncDecl<type_id::BOOL> *decl) {
}
void Interpreter::Visit(FuncDecl<type_id::STRING> *decl) {
}
void Interpreter::Visit(FuncDecl<type_id::INT> *decl) {
}

void Interpreter::Visit(Parameters *params) {

}

void Interpreter::Visit(ParamStmt<type_id::INT> *param) {

}

void Interpreter::Visit(ParamStmt<type_id::STRING> *param) {

}

void Interpreter::Visit(ParamStmt<type_id::BOOL> *param) {

}

void Interpreter::Visit(ParamStmt<type_id::VOID> *param) {

}

void Interpreter::Visit(ParamStmt<type_id::ID> *param) {

}


