#pragma once

#include "Types_codes.h"


struct ExpressionBase;

struct StatementBase;


//--------------------------Expressions------------------------------------
template <op_id op>
struct BinExpr;

template <type_id type>
struct NewExpr;

struct NotExpr;

struct IdExpr;

struct LitExpr;

struct Lvalue;


//------------------------Statements--------------------------

struct StatementsBlock;


struct AssertStmt;

struct DeclStmt;


struct IfStmt;

struct WhileStmt;

struct PrintStmt;

struct AssignStmt;

struct RetStmt;

struct CallStmt;

template <type_id type_id>
struct ParamStmt;

struct Parameters;

template <type_id type_id>
struct VarDecl;

template <type_id type_id>
struct FuncDecl;

struct ClassBody;

struct Class;

struct ClassesBlock;

struct MainFunc;

struct AST;