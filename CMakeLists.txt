cmake_minimum_required(VERSION 3.17)
project(JavaInterpreter)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(
        HEADERS
        ${JavaInterpreter_SOURCE_DIR}/driver.hh
        ${JavaInterpreter_SOURCE_DIR}/parser.hh
)

BISON_TARGET(
        JavaParser
        parser.y
        ${JavaInterpreter_SOURCE_DIR}/jpparser.cc
        DEFINES_FILE  ${JavaInterpreter_SOURCE_DIR}/jpparser.hh
)

FLEX_TARGET(
        JavaScanner
        scanner.l
        ${JavaInterpreter_SOURCE_DIR}/jpscanner.cc
)

ADD_FLEX_BISON_DEPENDENCY(JavaScanner JavaParser)

add_executable(
        JavaInterpreter
        main.cc
        driver.cc
        scanner.cc
        ${BISON_JavaParser_OUTPUTS}
        ${FLEX_JavaScanner_OUTPUTS}
        Visitor.h Forward_declarations.h Types_codes.h Interpreter.h Interpreter.cpp PrintVisitor.h PrintVisitor.cpp)

