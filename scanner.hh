#pragma once

#include <fstream>
#include <string>

#if !defined(yyFlexLexerOnce)

#define yyFlexLexer jpFlexLexer
#include "FlexLexer.h"
#endif

#undef YY_DECL
#define YY_DECL jp::parser::symbol_type jp::Scanner::ScanToken()

#include "jpparser.hh"
#include "location.hh"

namespace jp {
    class Scanner : public jpFlexLexer {
        jp::location loc;
    public:
        void restart(std::string &fname, std::ifstream &file);

        virtual jp::parser::symbol_type ScanToken();
    };
}
