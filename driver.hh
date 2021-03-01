#pragma once

#include <fstream>
#include <string>

#include "location.hh"
#include "jpparser.hh"
#include "scanner.hh"
#include "ast.hh"

namespace jp {
    class Driver {
    public:
        Driver();

        AST parse(std::string &fname);

        friend class jp::parser;

    private:
        jp::Scanner scanner;
        jp::parser parser;

        std::ifstream stream;

        AST result;
    };
}
