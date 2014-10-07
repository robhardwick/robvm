#
# Flex & Bison
#

set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH}
    /usr/local/opt/bison/bin
    /usr/local/opt/flex/bin)

find_package(BISON)
find_package(FLEX)

FLEX_TARGET(rvm_lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/parse/lexer.l
    ${PROJECT_BINARY_DIR}/lexer.c
    COMPILE_FLAGS "--header-file=${PROJECT_BINARY_DIR}/lexer.h")

BISON_TARGET(rvm_parser
    ${CMAKE_CURRENT_SOURCE_DIR}/parse/parser.y
    ${PROJECT_BINARY_DIR}/parser.c)

ADD_FLEX_BISON_DEPENDENCY(rvm_lexer rvm_parser)

include_directories(${PROJECT_BINARY_DIR})

#
# Readline
#

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
    /usr/local/opt/readline/include)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
    /usr/local/opt/readline/lib)

find_package(Readline)
include_directories(${READLINE_INCLUDE_DIRS})

#
# Talloc
#

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
    /usr/local/opt/talloc/include)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
    /usr/local/opt/talloc/lib)

find_package(Talloc)
include_directories(${TALLOC_INCLUDE_DIRS})

#
# Compile
#

add_library(librobvm STATIC
    app.c
    ast.c
    vm.c
    stack.c
    sym.c
    util.c
    ${BISON_rvm_parser_OUTPUTS}
    ${FLEX_rvm_lexer_OUTPUTS}
)

target_link_libraries(librobvm ${READLINE_LIBRARIES})
target_link_libraries(librobvm ${TALLOC_LIBRARIES})
