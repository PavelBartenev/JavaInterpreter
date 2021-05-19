#include <iostream>
#include <fstream>
#include <string>
#include "driver.hh"
#include "ast.hh"
#include "Interpreter.h"
#include "PrintVisitor.h"
#include "SymbolTableVisitor.h"
#include "SymbolsAndScopes/VarSymbol.h"
#include "SymbolsAndScopes/ClassSymbol.h"
#include "SymbolsAndScopes/MethodSymbol.h"


int main(int argc, char** argv) {
    std::string fname(argv[1]);
    jp::Driver driver;

    AST* result = driver.parse(fname);

    SymbolTableVisitor symbol_visitor;
    symbol_visitor.BuildScopesTree(result);

    if (std::string(argv[2]) == "execute") {
         Interpreter interpreter;
         interpreter.Interpret(result);
    } else if (std::string(argv[2]) == "tree") {
         PrintVisitor print_visitor;
         print_visitor.PrintTree(result);
    }

    //Check the symboltree: get the name of the second argument
    auto class_k_scope  = dynamic_cast<ClassSymbol*>(symbol_visitor.GetScope()->elements["MyClass"])->own_scope;
    std::cout << "\n" << dynamic_cast<MethodSymbol*>(class_k_scope->elements["foo"])->params[1]->name;

    return 0;
}
