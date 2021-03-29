%skeleton "lalr1.cc"
%require "3.5"

%defines

%locations

//%define parse.trace

%define api.token.constructor

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
   ELSE     "else"
   QUOTES   "\""
;

%token <int>            int     "Int"
%token <float>          float   "Float"
%token <std::string>    id      "id"
%token <std::string>    string  "string"

%nterm <AST>              programm
%nterm <MainFunc*>        main_func
%nterm <ClassesBlock*>    classes_block
%nterm <Class*>           class
%nterm <ClassBody*>       class_body
%nterm <StatementBase*>   funcdecl
%nterm <StatementBase*>   vardecl
%nterm <Parameters*>      parameters
%nterm <StatementBase*>   parameter
%nterm <StatementsBlock*> statements_block
%nterm <StatementBase*>   statement
%nterm <StatementBase*>   statements_group
%nterm <ExpressionBase*>  expression
%nterm <op_id>            binop
%nterm <type_id>          type
%nterm <Lvalue*>          lvalue
%nterm <CallStmt*>        method_invocation
%%

%left "||";
%left "&&";
%left ">" "<" "==";
%left "+" "-" "%";
%left "*" "/";

%start programm;

NLS: NEWLINE | NEWLINE NLS

MBNLS: %empty | NLS

programm:
    main_func[code] NLS classes_block[decls]
    { driver.result = new AST($code, $decls); }

main_func:
    INT MAIN LPAREN RPAREN MBNLS LBRACE MBNLS statements_block[code] RBRACE
    { $$ = new MainFunc($code); }

classes_block:
    %empty
    { $$ = new ClassesBlock(); }
    | class[next] NLS classes_block[other]
    { $$ = new ClassesBlock($next, $other); }

class:
    CLASS id MBNLS LBRACE MBNLS class_body[body] MBNLS RBRACE
    { $$ = new Class($id, $body); }

class_body:
    %empty
    { $$ = new ClassBody(); }
    | vardecl[var] SEMICOL NLS class_body[other]
    { $$ = new ClassBody($var, $other); }
    | funcdecl[func] NLS class_body[other]
    { $$ = new ClassBody($func, $other); }

funcdecl:
    PUBLIC type[retval_type] id LPAREN parameters[params] RPAREN MBNLS LBRACE MBNLS statements_block[code] RBRACE
    { switch($retval_type) {
         case type_id::INT :
             $$ = new FuncDecl<type_id::INT>($id, $params, $code);
             break;
         case type_id::BOOL :
             $$ = new FuncDecl<type_id::BOOL>($id, $params, $code);
             break;
         case type_id::VOID :
             $$ = new FuncDecl<type_id::VOID>($id, $params, $code);
             break;
         case type_id::ID :
             $$ = new FuncDecl<type_id::ID>($id, $params, $code);
             break;
         case type_id::STRING :
             $$ = new FuncDecl<type_id::STRING>($id, $params, $code);
             break;
      }
    }

vardecl:
    type[var_type] id
    { switch($var_type) {
         case type_id::INT :
                   $$ = new VarDecl<type_id::INT>($id);
                   break;
         case type_id::BOOL :
                   $$ = new VarDecl<type_id::BOOL>($id);
                   break;
         case type_id::VOID :
                   $$ = new VarDecl<type_id::VOID>($id);
                   break;
         case type_id::ID :
                   $$ = new VarDecl<type_id::ID>($id);
                   break;
         case type_id::STRING :
                   $$ = new VarDecl<type_id::STRING>($id);
                   break;
      }
    }

parameters:
    %empty
    { $$ = new Parameters(); }
    | parameter[param] parameters[other]
    { $$ = new Parameters($param, $other); }

parameter:
    type[param_type] id
    { switch($param_type) {
	case type_id::INT :
		 $$ = new ParamStmt<type_id::INT>($id);
		 break;
	case type_id::BOOL :
		 $$ = new ParamStmt<type_id::BOOL>($id);
		 break;
	case type_id::VOID :
		 $$ = new ParamStmt<type_id::VOID>($id);
		 break;
	case type_id::ID :
		 $$ = new ParamStmt<type_id::ID>($id);
		 break;
	case type_id::STRING :
		 $$ = new ParamStmt<type_id::STRING>($id);
		 break;
       }
    }
    | COMMA type[param_type] id
    { switch($param_type) {
	     case type_id::INT :
		       $$ = new ParamStmt<type_id::INT>($id);
		       break;
	     case type_id::BOOL :
		       $$ = new ParamStmt<type_id::BOOL>($id);
		       break;
	     case type_id::VOID :
		       $$ = new ParamStmt<type_id::VOID>($id);
		       break;
	     case type_id::ID :
		       $$ = new ParamStmt<type_id::ID>($id);
		       break;
	     case type_id::STRING :
		       $$ = new ParamStmt<type_id::STRING>($id);
		       break;
      }
    }

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
    { $$ = new StatementsBlock(); }
    | MBNLS statement[code] SEMICOL MBNLS statements_block[other]
    { $$ = new StatementsBlock($code, $other); }
    | MBNLS LBRACE MBNLS statements_block[this] RBRACE MBNLS
    { $$ = new StatementsBlock($this); }
    | MBNLS statements_group[code] NLS statements_block[other]
    { $$ = new StatementsBlock($code, $other); }

statement:
    ASSERT LPAREN expression[code] RPAREN
    { $$ = new AssertStmt($code); }
    | vardecl[decl]
    { $$ = $decl; }
    | PRINT LPAREN expression[code] RPAREN
    { $$ = new PrintStmt($code); }
    | lvalue[var] ASSIGN expression[code]
    { $$ = new AssignStmt($var, $code); }
    | RET expression[code]
    { $$ = new RetStmt($code); }
//    | method_invocation[call] SEMICOL
//    { $$ = new CallStmt($call); }

statements_group:
     IF LPAREN expression[cond] RPAREN MBNLS LBRACE MBNLS statements_block[code] MBNLS RBRACE
     { $$ = new IfStmt($cond, $code); }
     | IF LPAREN expression[cond] RPAREN MBNLS LBRACE MBNLS statements_block[code] MBNLS RBRACE ELSE MBNLS LBRACE MBNLS statements_block[other_code] MBNLS RBRACE
     { $$ = new IfStmt($cond, $code, $other_code); }
     | WHILE LPAREN expression[cond] RPAREN MBNLS LBRACE MBNLS statements_block[code] MBNLS RBRACE
     { $$ = new WhileStmt($cond, $code); }

method_invocation:
   TODO
    {}

field_invocation:
    TODO
    {}

lvalue:
    id
    { $$ = new Lvalue($id); }

expression:
    expression[first] binop[op] expression[second]
    { switch($op) {
	   case op_id::AND :
		     $$ = new BinExpr<op_id::AND>($first, $second);
		     break;
	   case op_id::OR :
		     $$ = new BinExpr<op_id::OR>($first, $second);
		     break;
	   case op_id::LESS :
		     $$ = new BinExpr<op_id::LESS>($first, $second);
		     break;
	   case op_id::GREATER :
		     $$ = new BinExpr<op_id::GREATER>($first, $second);
		     break;
	   case op_id::EQUAL :
		     $$ = new BinExpr<op_id::EQUAL>($first, $second);
		     break;
	   case op_id::PLUS :
		     $$ = new BinExpr<op_id::PLUS>($first, $second);
		     break;
	   case op_id::MINUS :
		     $$ = new BinExpr<op_id::MINUS>($first, $second);
		     break;
	   case op_id::STAR :
		     $$ = new BinExpr<op_id::STAR>($first, $second);
		     break;
	   case op_id::SLASH :
		     $$ = new BinExpr<op_id::SLASH>($first, $second);
		     break;
	   case op_id::PERCENT :
		     $$ = new BinExpr<op_id::PERCENT>($first, $second);
		     break;
      }
    }
    | NEW type[obj_type] LPAREN RPAREN
    { switch($obj_type) {
	     case type_id::INT :
		       $$ = new NewExpr<type_id::INT>();
		       break;
	     case type_id::BOOL :
		       $$ = new NewExpr<type_id::BOOL>();
		       break;
	     case type_id::VOID :
		       $$ = new NewExpr<type_id::VOID>();
		       break;
	     case type_id::ID :
		       $$ = new NewExpr<type_id::ID>();
		       break;
	     case type_id::STRING :
		       $$ = new NewExpr<type_id::STRING>();
		       break;
       }
    }
    | NOT expression[expr]
    { $$ = new NotExpr($expr); }
    | LPAREN expression[expr] RPAREN
    { $$ = $expr; }
    | id
    { $$ = new IdExpr($id); }
    | int[val]
    { $$ = new LitExpr($val); }
    | string[val]
    {  if ($val.length() == 2) {
    	   $val = "";
       } else {
       	   $val.pop_back();
           $val.erase(0, 1);
       }
       $$ = new LitExpr($val); }
//    | bool[val]
//    { $$ = new LitExpr($val); }

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









