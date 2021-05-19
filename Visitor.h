#pragma once

#include "Forward_declarations.h"

class Visitor {
public:
    virtual void Visit(AST* ast) = 0;
    virtual void Visit(MainFunc* main) = 0;
    virtual void Visit(ClassesBlock* classes) = 0;
    virtual void Visit(StatementsBlock* statements) = 0;
    virtual void Visit(Class* some_class) = 0;
    virtual void Visit(ClassBody* class_body) = 0;
    virtual void Visit(IfStmt* if_stmt) = 0;
    virtual void Visit(RetStmt* ret_stmt) = 0;
    virtual void Visit(LitExpr* lit_expr) = 0;
    virtual void Visit(NotExpr* not_expr) = 0;
    virtual void Visit(PrintStmt* print) = 0;

    virtual void Visit(VarDecl<type_id::INT>* decl) = 0;
    virtual void Visit(VarDecl<type_id::STRING>* decl) = 0;
    virtual void Visit(VarDecl<type_id::BOOL>* decl) = 0;
    virtual void Visit(VarDecl<type_id::ID>* decl) = 0;
    virtual void Visit(VarDecl<type_id::VOID>* decl) = 0;

    virtual void Visit(IdExpr* id) = 0;
    virtual void Visit(Lvalue* val) = 0;
    virtual void Visit(AssignStmt* assign) = 0;

    virtual void Visit(BinExpr<op_id::PLUS>* plus_expr) = 0;
    virtual void Visit(BinExpr<op_id::MINUS>* minus_expr) = 0;
    virtual void Visit(BinExpr<op_id::STAR>* mul_expr) = 0;
    virtual void Visit(BinExpr<op_id::SLASH>* div_expr) = 0;
    virtual void Visit(BinExpr<op_id::EQUAL>* equal_expr) = 0;
    virtual void Visit(BinExpr<op_id::AND>* and_expr) = 0;
    virtual void Visit(BinExpr<op_id::OR>* or_expr) = 0;
    virtual void Visit(BinExpr<op_id::LESS>* less_expr) = 0;
    virtual void Visit(BinExpr<op_id::GREATER>* greater_expr) = 0;
    virtual void Visit(BinExpr<op_id::PERCENT>* percent_expr) = 0;
    virtual void Visit(WhileStmt* while_stmt) = 0;

    virtual void Visit(FuncDecl<type_id::INT>* decl) = 0;
    virtual void Visit(FuncDecl<type_id::STRING>* decl) = 0;
    virtual void Visit(FuncDecl<type_id::BOOL>* decl) = 0;
    virtual void Visit(FuncDecl<type_id::ID>* decl) = 0;
    virtual void Visit(FuncDecl<type_id::VOID>* decl) = 0;

    virtual void Visit(Parameters* params) = 0;
    virtual void Visit(ParamStmt<type_id::INT>* param) = 0;
    virtual void Visit(ParamStmt<type_id::STRING>* param) = 0;
    virtual void Visit(ParamStmt<type_id::BOOL>* param) = 0;
    virtual void Visit(ParamStmt<type_id::VOID>* param) = 0;
    virtual void Visit(ParamStmt<type_id::ID>* param) = 0;
};
