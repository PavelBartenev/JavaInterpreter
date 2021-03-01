%{
    #include <stdlib.h>

    #include "jpparser.hh"
    #include "scanner.hh"
%}

%option noyywrap nounput noinput batch debug
%option c++
%option prefix="jp"
%option yyclass="Scanner"

id      [a-zA-z][a-zA-Z_0-9]*
int     [0-9]*
float   [0-9]+\.[0-9]*
blank   [ \t\r]

%{
    #define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
    loc.step();
%}

{blank}+  loc.step();


"{"     return jp::parser::make_LBRACE  (loc);
"}"     return jp::parser::make_RBRACE  (loc);
"("     return jp::parser::make_LPAREN  (loc);
")"     return jp::parser::make_RPAREN  (loc);
"="     return jp::parser::make_ASSIGN  (loc);
"+"     return jp::parser::make_PLUS    (loc);
"-"     return jp::parser::make_MINUS   (loc);
"*"     return jp::parser::make_STAR    (loc);
"/"     return jp::parser::make_SLASH   (loc);
"|"     return jp::parser::make_VERTBAR (loc);
"%"     return jp::parser::make_PERCENT (loc);
";"     return jp::parser::make_SEMICOL (loc);
"."     return jp::parser::make_DOT     (loc);
"int"   return jp::parser::make_INT     (loc);
"bool"  return jp::parser::make_BOOL    (loc);
"void"  return jp::parser::make_VOID    (loc);
"main"  return jp::parser::make_MAIN    (loc);
"print" return jp::parser::make_PRINT   (loc);

\n+       { loc.lines(yyleng); loc.step();
            return  jp::parser::make_NEWLINE(loc);
          }

{int}     return jp::parser::make_int     (atoi(yytext), loc);
{float}   return jp::parser::make_float   (atof(yytext), loc);
{id}      return jp::parser::make_id      (yytext, loc);

<<EOF>>  return jp::parser::make_END    (loc);
%%