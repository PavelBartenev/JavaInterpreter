#include "SymbolTableVisitor.h"
#include "ast.hh"
#include <iostream>
#include <string>
#include "SymbolsAndScopes/BaseSymbol.h"
#include "SymbolsAndScopes/MethodSymbol.h"
#include "SymbolsAndScopes/VarSymbol.h"
#include "SymbolsAndScopes/ClassSymbol.h"


void SymbolTableVisitor::Visit(AST *ast) {
    ast->classes->Accept(this);
    ast->main->Accept(this);
}

void SymbolTableVisitor::Visit(MainFunc* main) {
    main->block->Accept(this);
}

void SymbolTableVisitor::Visit(ClassesBlock* classes) {
    auto parent_scope = GetScope();

    for (auto& class_decl : classes->classes) {
        auto next_scope = new BaseScope();
        auto new_class = new ClassSymbol(class_decl->id, parent_scope, next_scope);
        parent_scope->elements[class_decl->id] = new_class;
        next_scope->parent = parent_scope;
        SetScope(next_scope);
        class_decl->body->Accept(this);
    }

    SetScope(parent_scope);
}

void SymbolTableVisitor::Visit(StatementsBlock* statements) {
    for (auto& stmt : statements->statements) {
        stmt->Accept(this);
    }
}

void SymbolTableVisitor::Visit(ClassBody* class_body) {
    for (auto& stmt : class_body->stmts) {
        stmt->Accept(this);
    }
}

void SymbolTableVisitor::Visit(VarDecl<type_id::INT>* decl) {
    auto scope = GetScope();
    scope->elements[decl->id] =  new VarSymbol(decl->id, "int", scope);
}

void SymbolTableVisitor::Visit(VarDecl<type_id::STRING>* decl) {
    auto scope = GetScope();
    scope->elements[decl->id] =  new VarSymbol(decl->id, "string", scope);
}

void SymbolTableVisitor::Visit(VarDecl<type_id::BOOL>* decl) {
    auto scope = GetScope();
    scope->elements[decl->id] =  new VarSymbol(decl->id, "bool", scope);
}

void SymbolTableVisitor::Visit(VarDecl<type_id::ID>* decl) {
    auto scope = GetScope();
    scope->elements[decl->id] =  new VarSymbol(decl->id, "id", scope);
}

void SymbolTableVisitor::Visit(VarDecl<type_id::VOID>* decl) {
    auto scope = GetScope();
    scope->elements[decl->id] = new VarSymbol(decl->id, "void", scope);
}

BaseScope *SymbolTableVisitor::GetScope() {
    if (current_scope == nullptr) {
        current_scope = new BaseScope();
    }
    return current_scope;
}

void SymbolTableVisitor::SetScope(BaseScope *scope) {
    current_scope = scope;
}

void SymbolTableVisitor::BuildScopesTree(AST *ast) {
    ast->Accept(this);
}

void SymbolTableVisitor::Visit(FuncDecl<type_id::INT> *decl) {
    auto parent_scope = GetScope();
    auto next_scope = new BaseScope();
    next_scope->parent = parent_scope;

    std::vector<VarSymbol*> params;
    for (auto& param : decl->params->params) {
        param->Accept(this);
        params.emplace_back(new VarSymbol(cur_param_name, cur_param_type, next_scope));
    }

    auto method = new MethodSymbol("int", params, decl->id, parent_scope, next_scope);
    parent_scope->elements[decl->id] = method;

    SetScope(next_scope);
    decl->code->Accept(this);
    SetScope(parent_scope);
}

void SymbolTableVisitor::Visit(ParamStmt<type_id::INT> *param) {
    cur_param_type = "int";
    cur_param_name = param->id;
}

void SymbolTableVisitor::Visit(ParamStmt<type_id::STRING> *param) {
    cur_param_type = "string";
    cur_param_name = param->id;
}

void SymbolTableVisitor::Visit(ParamStmt<type_id::BOOL> *param) {
    cur_param_type = "bool";
    cur_param_name = param->id;
}

void SymbolTableVisitor::Visit(ParamStmt<type_id::VOID> *param) {
    cur_param_type = "void";
    cur_param_name = param->id;
}

void SymbolTableVisitor::Visit(ParamStmt<type_id::ID> *param) {
    cur_param_type = "id";
    cur_param_name = param->id;
}


void SymbolTableVisitor::Visit(FuncDecl<type_id::STRING> *decl) {
}
void SymbolTableVisitor::Visit(FuncDecl<type_id::BOOL> *decl) {
}
void SymbolTableVisitor::Visit(FuncDecl<type_id::ID> *decl) {
}
void SymbolTableVisitor::Visit(FuncDecl<type_id::VOID> *decl) {
}
void SymbolTableVisitor::Visit(Parameters *params) {
}
void SymbolTableVisitor::Visit(IdExpr* id) {
}
void SymbolTableVisitor::Visit(Lvalue* val) {
}
void SymbolTableVisitor::Visit(AssignStmt* assign) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::PLUS>* plus_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::MINUS>* minus_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::STAR>* mul_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::SLASH>* div_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::EQUAL>* equal_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::AND>* and_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::OR>* or_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::LESS>* less_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::GREATER>* greater_expr) {
}
void SymbolTableVisitor::Visit(BinExpr<op_id::PERCENT>* percent_expr) {
}
void SymbolTableVisitor::Visit(WhileStmt* while_stmt) {
}
void SymbolTableVisitor::Visit(IfStmt* if_stmt) {
}
void SymbolTableVisitor::Visit(RetStmt* ret_stmt) {
}
void SymbolTableVisitor::Visit(LitExpr* lit_expr) {
}
void SymbolTableVisitor::Visit(NotExpr* not_expr) {
}
void SymbolTableVisitor::Visit(PrintStmt* print) {
}
void SymbolTableVisitor::Visit(Class* some_class) {
}