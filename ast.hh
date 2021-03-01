#pragma once

#include <iostream>
#include <string>
#include <list>
#include <utility>

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
    ID
};

struct ExpressionBase {
};

struct StatementBase {
};


//--------------------------Expressions------------------------------------

template <int op_id>
struct BinExpr : public ExpressionBase {
    ExpressionBase* first;
    ExpressionBase* second;

    BinExpr(ExpressionBase* first, ExpressionBase* second) :
    first(first), second(second) {}
};

template <int type_id>
struct NewExpr : public ExpressionBase {
};

struct NotExpr : public ExpressionBase {
    ExpressionBase* expr;


    NotExpr(ExpressionBase* expr) :
    expr(expr) {}
};

struct IdExpr : public ExpressionBase {
    std::string id;

    IdExpr(const std::string& id) :
    id(id) {}
};

struct NumExpr : public ExpressionBase {
    int number;

    NumExpr(int number) :
    number(number) {}
};


//------------------------Statements--------------------------

struct StatementsBlock : public StatementBase {
    std::list<StatementBase*> statements;

    StatementsBlock() = default;

    StatementsBlock(StatementBase* code, StatementsBlock* other) :
    statements(other->statements) {
        statements.push_front(code);
    }
};


struct AssertStmt : public StatementBase {
    ExpressionBase* expr;

    AssertStmt(ExpressionBase* expr) :
    expr(expr) {}
};

struct DeclStmt : StatementBase {
  //???
};


struct IfStmt : StatementBase {
    ExpressionBase* condition;
    StatementsBlock* then;
    StatementsBlock* if_not = nullptr;

    IfStmt(ExpressionBase* condition, StatementsBlock* code) :
    condition(condition), then(code) {}

    IfStmt(ExpressionBase* condition, StatementsBlock* then, StatementsBlock* if_not) :
    condition(condition), then(then), if_not(if_not) {}
};

struct WhileStmt : StatementBase {
    ExpressionBase* condition;
    StatementsBlock* code;

    WhileStmt(ExpressionBase* cond, StatementsBlock* code) :
    condition(cond), code(code) {}
};

struct PrintStmt : StatementBase {
    ExpressionBase* expr;

    PrintStmt(ExpressionBase* expr) :
    expr(expr) {}
};

struct AssignStmt : public StatementBase {
    ExpressionBase* var;
    ExpressionBase* code;

    AssignStmt(ExpressionBase* var, ExpressionBase* code) :
    var(var), code(code) {}
};

struct RetStmt : public StatementBase {
    ExpressionBase* code;

    RetStmt(ExpressionBase* code) :
    code(code) {}
};

struct CallStmt : public StatementBase {

};




























