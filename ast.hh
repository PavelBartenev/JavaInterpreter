#pragma once

#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <variant>

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
    STRING
};

type_id GetType(SomeType& obj) {
    if (std::holds_alternative<int>(obj)) {
        return type_id::INT;
    } else if (std::holds_alternative<bool>(obj)){
        return type_id::BOOL;
    } else if (std::holds_alternative<std::string>(obj)){
        return type_id::STRING;
    }
}

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
   //TODO();
};

template <type_id type_id>
struct ParamStmt : public StatementBase {
    std::string id;

    ParamStmt(std::string& id) :
    id(id) {}
};

struct Parameters : StatementBase {
    std::list<StatementBase*> params;

    Parameters() = default;

   Parameters(StatementBase* param, Parameters* other) :
   params(other->params) {
       params.push_front(param);
   }
};

template <type_id type_id>
struct VarDecl : StatementBase {
    std::string id;

    VarDecl(std::string& id) :
    id(id) {}
};

template <type_id type_id>
struct FuncDecl : StatementBase {
    std::string id;
    Parameters* params;
    StatementsBlock* code;

    FuncDecl(std::string& id, Parameters* params, StatementsBlock* code) :
    id(id), params(params), code(code) {}
};

struct ClassBody :  StatementBase {
    std::list<StatementBase*> stmts;

    ClassBody() = default;

    ClassBody(StatementBase* stmt, ClassBody* other)
    : stmts(other->stmts) {
        stmts.push_front(stmt);
    }
};

struct Class : StatementBase {
    ClassBody* body;
    std::string id;

    Class(ClassBody* body, std::string& id) :
    body(body), id(id) {}
};

struct ClassesBlock : StatementBase {
    std::list<Class*> classes;

    ClassesBlock() = default;

    ClassesBlock(Class* next, ClassesBlock* other) :
    classes(other->classes) {
        classes.push_front(next);
    }
};






























