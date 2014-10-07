%{
#include "robvm.h"
#include "parser.h"
#include "lexer.h"

#define AST_VAL(node, type, value) \
    node = rvm_ast_init(root, type, value);

#define AST_EXP(node, type, first, second) \
    node = rvm_ast_init(root, type, NULL); \
    rvm_ast_append(node, first); \
    rvm_ast_append(node, second);

int yyerror(rvm_ast_node_t *root, const char *msg);
%}

%pure-parser
%parse-param {rvm_ast_node_t *root}

%union {
  char op;
  char *val;
  rvm_ast_node_t *node;
};

%token <val> IDENTIFIER STRING INTEGER FLOAT
%token <op> ASSIGN ADD SUBTRACT MULTIPLY DIVIDE LPAREN RPAREN EQUAL END
%type  <node> expression statement

%%

input:
    statement
    | input statement
    ;

statement:
    END                                 { }
    | expression END                    { rvm_ast_append(root, $1); }
    ;

expression:
    IDENTIFIER                          { AST_VAL($$, RVM_AST_IDENTIFIER, $1) }
    | INTEGER                           { AST_VAL($$, RVM_AST_INTEGER, $1) }
    | FLOAT                             { AST_VAL($$, RVM_AST_FLOAT, $1) }
    | STRING                            { AST_VAL($$, RVM_AST_STRING, $1) }
    | expression ASSIGN expression      { AST_EXP($$, RVM_AST_ASSIGN, $1, $3) }
    | expression ADD expression         { AST_EXP($$, RVM_AST_ADD, $1, $3) }
    | expression SUBTRACT expression    { AST_EXP($$, RVM_AST_SUBTRACT, $1, $3) }
    | expression MULTIPLY expression    { AST_EXP($$, RVM_AST_MULTIPLY, $1, $3) }
    | expression DIVIDE expression      { AST_EXP($$, RVM_AST_DIVIDE, $1, $3) }
    | LPAREN expression RPAREN          { $$ = $2; }
    ;

%%

int yyerror(rvm_ast_node_t *root, const char *msg) {
    rvm_log(RVM_LOG_ERR, msg);
    return 0;
}
