#include "scanner.hh"

namespace jp {
    void Scanner::restart(std::string &fname, std::ifstream &file) {
        loc.initialize(&fname);
        yyrestart(&file);
    }
}
