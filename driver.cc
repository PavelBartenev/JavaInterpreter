#include "driver.hh"
#include <string>
#include "ast.hh"

namespace jp {
    Driver::Driver() : scanner(), parser(scanner, *this) {
        parser.set_debug_level(1);
    }

    AST Driver::parse(std::string &fname) {
        stream.open(fname);
        scanner.restart(fname, stream);
        parser();
        stream.close();
        return result;
    }
}