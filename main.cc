#include <iostream>
#include <fstream>
#include <string>
#include "driver.hh"
#include "ast.hh"
#include "Interpreter.h"
#include "PrintVisitor.h"


int main(int argc, char** argv) {
    std::string fname(argv[1]);
    jp::Driver driver;

    AST* result = driver.parse(fname);

    if (std::string(argv[2]) == "execute") {
         Interpreter interpreter;
         interpreter.Interpret(result);
    } else if (std::string(argv[2]) == "tree") {
         PrintVisitor print_visitor;
         print_visitor.PrintTree(result);
    }

    return 0;
}
