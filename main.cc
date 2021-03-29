#include <iostream>
#include <fstream>
#include <string>
#include "driver.hh"
#include "ast.hh"
#include "Interpreter.h"

int main(int argc, char** argv) {
    std::string fname(argv[1]);
    jp::Driver driver;

    AST* result = driver.parse(fname);

    Interpreter interpreter;

    interpreter.Interpret(result);

  //  std::cout << std::get<int>(interpreter.variables.at("x"));
   // std::cout << dynamic_cast<VarDecl<type_id::INT>*>(result.main->block->statements.front())->id;


    return 0;
}

