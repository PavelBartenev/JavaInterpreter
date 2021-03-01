#include <iostream>
#include <fstream>
#include <string>
#include "driver.hh"
#include "ast.hh"


int main(int argc, char** argv) {
    std::string fname(argv[1]);
    jp::Driver driver;

    AST result = driver.parse(fname);



    return 0;
}

