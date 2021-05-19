#include "PrintVisitor.h"
#include "ast.hh"
#include <iostream>
#include <string>


int PrintVisitor::PrintTree(AST *ast) {
    ast->Accept(this);

    return 0;
}

void PrintVisitor::Visit(MainFunc *main) {
    std::string spaces(level, '\t');

    std::cout << spaces << "main start\n";

    ++level;
    main->block->Accept(this);
    --level;

    std::cout << spaces << "main end\n";
}

void PrintVisitor::Visit(ClassesBlock *classes) {
    for (auto& some_class : classes->classes)
        some_class->Accept(this);
}

void PrintVisitor::Visit(Class *some_class) {
    std::string spaces(level, '\t');

    std::cout << spaces << "class " << some_class->id << " start\n";
    ++level;
    some_class->body->Accept(this);
    --level;
    std::cout << spaces <<  "class " << some_class->id << " end\n";
}

void PrintVisitor::Visit(ClassBody *class_body) {
    ++level;
    for (auto& stmt : class_body->stmts)
        stmt->Accept(this);
    --level;
}

void PrintVisitor::Visit(StatementsBlock *statements) {
    std::string spaces(level, '\t');

    std::cout << spaces << "statements start\n";

    ++level;

    for (auto& stmt : statements->statements) {
        stmt->Accept(this);
    }

    --level;

    std::cout << spaces << "statements end\n";
}

void PrintVisitor::Visit(IfStmt *if_stmt) {
    std::string spaces(level, '\t');

    std::cout << spaces << "IfStmt start\n";

    ++level;
    if_stmt->condition->Accept(this);
    if (if_stmt->then) {
        if_stmt->then->Accept(this);
    }
    if (if_stmt->if_not) {
        if_stmt->if_not->Accept(this);
    }
    --level;

    std::cout << spaces << "IfStmt end\n";
}

void PrintVisitor::Visit(LitExpr *lit_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "literal\n";
}

void PrintVisitor::Visit(NotExpr *not_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Not start\n";

    ++level;
    not_expr->expr->Accept(this);
    --level;

    std::cout << spaces << "Not end\n";
}

void PrintVisitor::Visit(RetStmt *ret_stmt) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Return start\n";

    ++level;
    ret_stmt->code->Accept(this);
    --level;

    std::cout << spaces << "Return end\n";
}

void PrintVisitor::Visit(PrintStmt *print) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Print start\n";

    ++level;
    print->expr->Accept(this);
    --level;

    std::cout << spaces << "Print end\n";
}

void PrintVisitor::Visit(VarDecl<type_id::INT> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "IntDeclaration start\n";

    std::cout << spaces << "    " << decl->id << "\n";

    std::cout << spaces << "IntDeclaration end\n";
}

void PrintVisitor::Visit(VarDecl<type_id::STRING> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "StringDeclaration start\n";

    std::cout << spaces << "    " << decl->id << "\n";

    std::cout << spaces << "StringDeclaration end\n";
}

void PrintVisitor::Visit(VarDecl<type_id::BOOL> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "BoolDeclaration start\n";

    std::cout << spaces << "    " << decl->id << "\n";

    std::cout << spaces << "BoolDeclaration end\n";
}

void PrintVisitor::Visit(VarDecl<type_id::ID> *decl) {
    //TODO()
}

void PrintVisitor::Visit(VarDecl<type_id::VOID> *decl) {
    //TODO()
}

void PrintVisitor::Visit(IdExpr *id) {
    std::string spaces(level, '\t');

    std::cout << spaces << "IdExpr start\n";

    std::cout << spaces  << "   " << id->id << "\n";

    std::cout << spaces << "IdExpr end\n";
}

void PrintVisitor::Visit(Lvalue *val) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Lvalue start\n";

    std::cout << spaces << "    " << val->id << "\n";

    std::cout << spaces << "Lvalue end\n";
}

void PrintVisitor::Visit(AssignStmt *assign) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Assignment start\n";

    ++level;
    assign->var->Accept(this);
    assign->code->Accept(this);
    --level;

    std::cout << spaces << "Assignment end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::PLUS>* plus_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Add start\n";

    ++level;
    plus_expr->first->Accept(this);
    plus_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Add end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::MINUS> *minus_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Sub start\n";

    ++level;
    minus_expr->first->Accept(this);
    minus_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Sub end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::STAR> *mul_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Mul start\n";

    ++level;
    mul_expr->first->Accept(this);
    mul_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Mul end\n";

}

void PrintVisitor::Visit(BinExpr<op_id::SLASH> *div_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Div start\n";

    ++level;
    div_expr->first->Accept(this);
    div_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Div end\n";

}

void PrintVisitor::Visit(BinExpr<op_id::EQUAL> *equal_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Equal start\n";

    ++level;
    equal_expr->first->Accept(this);
    equal_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Equal end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::AND> *and_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "And start\n";

    ++level;
    and_expr->first->Accept(this);
    and_expr->second->Accept(this);
    --level;

    std::cout << spaces << "And end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::OR> *or_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Or start\n";

    ++level;
    or_expr->first->Accept(this);
    or_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Or end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::LESS> *less_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Less start\n";

    ++level;
    less_expr->first->Accept(this);
    less_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Less end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::GREATER> *greater_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Greater start\n";

    ++level;
    greater_expr->first->Accept(this);
    greater_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Greater end\n";
}

void PrintVisitor::Visit(BinExpr<op_id::PERCENT> *percent_expr) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Percent start\n";

    ++level;
    percent_expr->first->Accept(this);
    percent_expr->second->Accept(this);
    --level;

    std::cout << spaces << "Percent end\n";
}

void PrintVisitor::Visit(WhileStmt *while_stmt) {
    std::string spaces(level, '\t');

    std::cout << spaces << "While start\n";

    ++level;
    while_stmt->condition->Accept(this);
    while_stmt->code->Accept(this);
    --level;

    std::cout << spaces << "While end\n";
}

void PrintVisitor::Visit(AST *ast) {
    ast->main->Accept(this);
    std::cout << "\n";
    ast->classes->Accept(this);
}

void PrintVisitor::Visit(FuncDecl<type_id::INT> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Func declaration start\n";

    std::cout << spaces << "name: " << decl->id << "\n";
    std::cout << spaces << "ret type: " << "int" << "\n";
    std::cout << spaces << "parameters: \n";

    ++level;
    decl->params->Accept(this);

    std::cout << spaces << "body: \n";
    decl->code->Accept(this);
    --level;

    std::cout << spaces << "Func declaration end\n";
}

void PrintVisitor::Visit(FuncDecl<type_id::STRING> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Func declaration start\n";

    std::cout << spaces << "name: " << decl->id << "\n";
    std::cout << spaces << "ret type: " << "string" << "\n";
    std::cout << spaces << "parameters: \n";

    ++level;
    decl->params->Accept(this);

    std::cout << spaces << "body: \n";
    decl->code->Accept(this);
    --level;

    std::cout << spaces << "Func declaration end\n";
}

void PrintVisitor::Visit(FuncDecl<type_id::BOOL> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Func declaration start\n";

    std::cout << spaces << "name: " << decl->id << "\n";
    std::cout << spaces << "ret type: " << "bool" << "\n";
    std::cout << spaces << "parameters: \n";

    ++level;
    decl->params->Accept(this);

    std::cout << spaces << "body: \n";
    decl->code->Accept(this);
    --level;

    std::cout << spaces << "Func declaration end\n";
}

void PrintVisitor::Visit(FuncDecl<type_id::ID> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Func declaration start\n";

    std::cout << spaces << "name: " << decl->id << "\n";
    std::cout << spaces << "ret type: " << "id" << "\n";
    std::cout << spaces << "parameters: \n";

    ++level;
    decl->params->Accept(this);

    std::cout << spaces << "body: \n";
    decl->code->Accept(this);
    --level;

    std::cout << spaces << "Func declaration end\n";
}

void PrintVisitor::Visit(FuncDecl<type_id::VOID> *decl) {
    std::string spaces(level, '\t');

    std::cout << spaces << "Func declaration start\n";

    std::cout << spaces << "name: " << decl->id << "\n";
    std::cout << spaces << "ret type: " << "void" << "\n";
    std::cout << spaces << "parameters: \n";

    ++level;
    decl->params->Accept(this);

    std::cout << spaces << "body: \n";
    decl->code->Accept(this);
    --level;

    std::cout << spaces << "Func declaration end\n";
}

void PrintVisitor::Visit(Parameters *params) {
    for (auto& param : params->params)
        param->Accept(this);
}

void PrintVisitor::Visit(ParamStmt<type_id::INT> *param) {
    std::string spaces(level, '\t');
    std::cout << spaces << "int " << param->id << "\n";
}

void PrintVisitor::Visit(ParamStmt<type_id::STRING> *param) {
    std::string spaces(level, '\t');
    std::cout << spaces << "string " << param->id << "\n";
}

void PrintVisitor::Visit(ParamStmt<type_id::BOOL> *param) {
    std::string spaces(level, '\t');
    std::cout << spaces << "bool " << param->id << "\n";
}

void PrintVisitor::Visit(ParamStmt<type_id::VOID> *param) {
    std::string spaces(level, '\t');
    std::cout << spaces << "void " << param->id << "\n";
}

void PrintVisitor::Visit(ParamStmt<type_id::ID> *param) {
    std::string spaces(level, '\t');
    std::cout << spaces << "id " << param->id << "\n";
}