#pragma once

#include <iostream>
#include <string>
#include <list>
#include <utility>
#include "Visitor.h"
#include <variant>
#include "Types_codes.h"


struct ExpressionBase {

    virtual ~ExpressionBase(){};

    virtual void Accept(Visitor* visitor){}

};

struct StatementBase {
    virtual ~StatementBase(){};

    virtual void Accept(Visitor* visitor){}
};


//--------------------------Expressions------------------------------------
template <op_id op>
struct BinExpr : public ExpressionBase {
    ExpressionBase* first;
    ExpressionBase* second;

    BinExpr(ExpressionBase* first, ExpressionBase* second) :
    first(first), second(second) {}

    virtual ~BinExpr() {}

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

template <type_id type>
struct NewExpr : public ExpressionBase {
    virtual ~NewExpr() {

    }
};

struct NotExpr : public ExpressionBase {
    ExpressionBase* expr;

    NotExpr(ExpressionBase* expr) :
    expr(expr) {}

    virtual ~NotExpr() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct IdExpr : public ExpressionBase {
    std::string id;

    IdExpr(const std::string& id) :
    id(id) {}

    virtual ~IdExpr() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct LitExpr : public ExpressionBase {
    SomeType literal;

    LitExpr(const SomeType& literal) :
    literal(literal) {}

    virtual ~LitExpr() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct Lvalue : public ExpressionBase {
    std::string id;

    Lvalue(std::string& id) :
    id(id) {}

    virtual ~Lvalue() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};


//------------------------Statements--------------------------

struct StatementsBlock : public StatementBase {
    std::list<StatementBase*> statements;

    StatementsBlock() = default;

    StatementsBlock(StatementsBlock* other) :
    statements(other->statements) {}

    StatementsBlock(StatementBase* code, StatementsBlock* other) :
    statements(other->statements) {
        statements.push_front(code);
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

    virtual ~StatementsBlock() {
    }
};


struct AssertStmt : public StatementBase {
    ExpressionBase* expr;

    AssertStmt(ExpressionBase* expr) :
    expr(expr) {}

    virtual ~AssertStmt() {
    }
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

    virtual ~IfStmt() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct WhileStmt : StatementBase {
    ExpressionBase* condition;
    StatementsBlock* code;

    WhileStmt(ExpressionBase* cond, StatementsBlock* code) :
    condition(cond), code(code) {}

    virtual ~WhileStmt() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct PrintStmt : StatementBase {
    ExpressionBase* expr;

    PrintStmt(ExpressionBase* expr) :
    expr(expr) {}

    virtual ~PrintStmt() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct AssignStmt : public StatementBase {
    ExpressionBase* var;
    ExpressionBase* code;

    AssignStmt(ExpressionBase* var, ExpressionBase* code) :
    var(var), code(code) {}

    virtual ~AssignStmt() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct RetStmt : public StatementBase {
    ExpressionBase* code;

    RetStmt(ExpressionBase* code) :
    code(code) {}

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct CallStmt : public StatementBase {
   //TODO();
};

template <type_id type_id>
struct ParamStmt : public StatementBase {
    std::string id;

    ParamStmt(std::string& id) :
    id(id) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct Parameters : StatementBase {
    std::list<StatementBase*> params;

    Parameters() = default;

   Parameters(StatementBase* param, Parameters* other) :
   params(other->params) {
       params.push_front(param);
   }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

template <type_id type_id>
struct VarDecl : StatementBase {
    std::string id;

    VarDecl(std::string& id) :
    id(id) {}

    virtual ~VarDecl() {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

template <type_id type_id>
struct FuncDecl : StatementBase {
    std::string id;
    Parameters* params;
    StatementsBlock* code;

    FuncDecl(std::string& id, Parameters* params, StatementsBlock* code) :
    id(id), params(params), code(code) {}

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct ClassBody :  StatementBase {
    std::list<StatementBase*> stmts;

    ClassBody() = default;

    ClassBody(StatementBase* stmt, ClassBody* other)
    : stmts(other->stmts) {
        stmts.push_front(stmt);
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct Class : StatementBase {
    ClassBody* body;
    std::string id;

    Class(std::string& id, ClassBody* body) :
    body(body), id(id) {}

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct ClassesBlock : StatementBase {
    std::list<Class*> classes;

    ClassesBlock() = default;

    ClassesBlock(Class* next, ClassesBlock* other) :
    classes(other->classes) {
        classes.push_front(next);
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct MainFunc : StatementBase {
    StatementsBlock* block;

    MainFunc(StatementsBlock* block) :
    block(block) {}

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};

struct AST : StatementsBlock {
    MainFunc* main;
    ClassesBlock* classes;

    AST() = default;

    AST(MainFunc* main, ClassesBlock* classes) :
    main(main), classes(classes) {}

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};






























