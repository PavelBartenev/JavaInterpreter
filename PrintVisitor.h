#pragma once


#include "Visitor.h"
#include "Types_codes.h"

class PrintVisitor : public Visitor {
public:
    void Visit(AST* ast) override;
    void Visit(MainFunc* main) override;
    void Visit(ClassesBlock* classes) override;
    void Visit(StatementsBlock* statements) override;
    void Visit(Class* some_class) override;
    void Visit(ClassBody* class_body) override;
    void Visit(IfStmt* if_stmt) override;
    void Visit(RetStmt* ret_stmt) override;
    void Visit(LitExpr* lit_expr) override;
    void Visit(NotExpr* not_expr) override;
    void Visit(PrintStmt* print) override;

    void Visit(VarDecl<type_id::INT>* decl) override;
    void Visit(VarDecl<type_id::STRING>* decl) override;
    void Visit(VarDecl<type_id::BOOL>* decl) override;
    void Visit(VarDecl<type_id::ID>* decl) override;
    void Visit(VarDecl<type_id::VOID>* decl) override;

    void Visit(IdExpr* id) override;
    void Visit(Lvalue* val) override;
    void Visit(AssignStmt* assign) override;

    void Visit(BinExpr<op_id::PLUS>* plus_expr) override;
    void Visit(BinExpr<op_id::MINUS>* minus_expr) override;
    void Visit(BinExpr<op_id::STAR>* mul_expr) override;
    void Visit(BinExpr<op_id::SLASH>* div_expr) override;
    void Visit(BinExpr<op_id::EQUAL>* equal_expr) override;
    void Visit(BinExpr<op_id::AND>* and_expr) override;
    void Visit(BinExpr<op_id::OR>* or_expr) override;
    void Visit(BinExpr<op_id::LESS>* less_expr) override;
    void Visit(BinExpr<op_id::GREATER>* greater_expr) override;
    void Visit(BinExpr<op_id::PERCENT>* percent_expr) override;

    void Visit(WhileStmt* while_stmt) override;


    int PrintTree(AST* ast);

private:
    int level = 0;
};
