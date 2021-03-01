%skeleton "lalr1.cc"
%require "3.5"

%defines

// Enable locations support
%locations

// Enable tracing
%define parse.trace

// This option with next makes
// yylex to have signature
// as below
%define api.token.constructor

// Declare value type - variant
// Like union, but for C++
// Can store any C++ type
%define api.value.type variant

%define api.namespace {jp}

%define api.token.prefix {JP_}

%code requires{
	#include <string>
	#include "ast.hh"

	namespace jp {
	    class Scanner;
	    class Driver;
	}
}

%lex-param { jp::Scanner& scanner }

%parse-param { jp::Scanner& scanner }
%parse-param { jp::Driver& driver }


%code{
	#include "scanner.hh"
	#include "driver.hh"
	#include "location.hh"
	#include "ast.hh"

	static jp::parser::symbol_type yylex(jp::Scanner& scanner){
		return scanner.ScanToken();
	}
}


%token
   END 0    "EOF"
   NEWLINE  "\n"
   LBRACE   "{"
   RBRACE   "}"
   LPAREN   "("
   RPAREN   ")"
   ASSIGN   "="
   PLUS     "+"
   MINUS    "-"
   STAR     "*"
   SLASH    "/"
   VERTBAR  "|"
   PERCENT  "%"
   AND      "&&"
   OR       "||"
   LESS     "<"
   GREATER  ">"
   EQUAL    "=="
   SEMICOL  ";"
   DOT      "."
   INT      "int"
   BOOL     "bool"
   VOID     "void"
   MAIN     "main"
   PRINT    "print"
   CLASS    "class"
   PUBLIC   "public"
   COMMA    ","
   ASSERT   "assert"
   IF       "if"
   WHILE    "while"
   RET      "return"
   THIS     "this"
   TODO     "later"
   NEW      "new"
   NOT      "!"
;

%token <int>            int     "Int"
%token <float>          float   "Float"
%token <std::string>    id      "id"

%nterm <AST>              programm
%nterm <MainFunc*>        main_func
%nterm <CLassesBlock*>    classes_block
%nterm <Class*>           class
%nterm <ClassBody*>       class_body
%nterm <FuncDecl*>        funcdecl
%nterm <VarDecl*>         vardecl
%nterm <Parameters*>      parameters
%nterm <Parameter*>       parameter
%nterm <StatementsBlock*> statements_block
%nterm <StatementBase*>   statement
%nterm <ExpressionBase*>  expression
%nterm <op_id>            binop
%nterm <type_id>          type

%%
%start programm;

NLS: NEWLINE | NEWLINE NLS

programm:
    main_func[code] classes_block[decls]
    { driver.result = AST($code, $decls); }

main_func:
    INT MAIN LBRACE RBRACE NLS LPAREN statements_block[code] RBRACE
    { $$ = new MainFunc($code); }

classes_block:
    %empty
    { $$ = new ClassesBlock(); }
    | class[next] classes_block[other]
    { $$ = new ClassesBlock($next, $other); }

class:
    CLASS id LPAREN class_body[body] RPAREN
    { $$ = new Class($id, $body); }

class_body:
    %empty
    { $$ = new ClassBody(); }
    | vardecl[var] class_body[other]
    { $$ = new ClassBody($var, $other); }
    | funcdecl[func] class_body[other]
    { $$ = new ClassBody($func, $other); }

funcdecl:
    PUBLIC type[retval_type] id LBRACE parameters[params] RBRACE LPAREN statements_block[code] RPAREN
    { $$ = new FuncDecl<retval_type>($id, $params, $code); }

vardecl:
    type[var_type] id SEMICOL
    { $$ = VarDecl<var_type>($id); }

parameters:
    %empty
    { $$ = new Parameters(); }
    | parameter[param] parameters[other]
    { $$ = new Parameters($param, $other) }

parameter:
    type[param_type] id
    { $$ = new Parameter<param_type> ($id); }
    | COMMA type[param_type] id
    { $$ = new Parameter<param_type> ($id); }

type:
    INT
    {$$ = type_id::INT; }
    | BOOL
    {$$ = type_id::BOOL; }
    | VOID
    { $$ = type_id::VOID; }
    | id
    { $$ = type_id::ID; }

statements_block:
    %empty
    { $$ = StatementsBlock(); }
    | statement[code] statements_block[other]
    { $$ = StatementsBlock($code, $other); }
    | LPAREN statements_block[this] RPAREN
    { $$ = StatementsBlock($this); }

statement:
    ASSERT LBRACE expression[code] RBRACE
    { $$ = new AssertStmt($code); }
    | vardecl[decl]
    { $$ = new DeclStmt($decl); }
    | IF LBRACE expression[cond] RBRACE statements_block[code]
    { $$ = new IfStmt($cond, $code); }
    | IF LBRACE expression[cond] RBRACE statements_block[code] ELSE statements_block[other_code]
    { $$ = new IfStmt($cond, $code, $other_code); }
    | WHILE LBRACE expression[cond] RBRACE statements_block[code]
    { $$ = new WhileStmt($cond, $code); }
    | PRINT LBRACE expression[code] RBRACE SEMICOL
    { $$ = new PrintStmt($code); }
    | lvalue[var] ASSIGN expression[code] SEMICOL
    { $$ = new AssignStmt($var, $code); }
    | RET expression[code] SEMICOL
    { $$ = new RetStmt($code); }
    | method_invocation[call] SEMICOL
    { $$ = new CallStmt($call); }

method_invocation:
    TODO
    {}

field_invocation:
    TODO
    {}

lvalue:
    id
    { $$ = new IdExpr($id); }

expression:
    expression[first] binop[op] expression[second]
    { $$ = new BinExpr<$op>($first, $second); }
    | NEW type[obj_type] LBRACE RBARCE
    { $$ = new NewExpr<$obj_type>()); }
    | NOT expression[expr]
    { $$ = new NotExpr($expr); }
    | LBRACE expression[expr] RBRACE
    { $$ = $expr; }
    | id
    { $$ = new IdExpr($id); }
    | int[val]
    { $$ = new NumExpr($val); }

binop:
    AND
    { $$ = op_id::AND; }
    | OR
    { $$ = op_id::OR; }
    | LESS
    { $$ = op_id::LESS; }
    | GREATER
    { $$ = op_id::GREATER; }
    | EQUAL
    { $$ = op_id::EQUAL; }
    | PLUS
    { $$ = op_id::PLUS; }
    | MINUS
    { $$ = op_id::MINUS; }
    | STAR
    { $$ = op_id::STAR; }
    | SLASH
    { $$ = op_id::SLASH; }
    | PERCENT
    { $$ = op_id::PERCENT; }
%%

void jp::parser::error(const jp::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}









