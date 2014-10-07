%{
#include "robvm.h"
#include "parser.h"
%}

%option warn
%option nodefault
%option noyywrap
%option never-interactive
%option nounistd
%option bison-bridge
%option noinput
%option nounput

%%

[0-9]+          { yylval->val = yytext; return INTEGER; }
[0-9]+\.[0-9]+  { yylval->val = yytext; return FLOAT; }
[A-Za-z0-9_]+   { yylval->val = yytext; return IDENTIFIER; }
\"(\\.|[^"])*\" { yylval->val = yytext; return STRING;  }
"="             { return ASSIGN; }
"+"             { return ADD; }
"-"             { return SUBTRACT; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"("             { return LPAREN; }
")"             { return RPAREN; }
";"             { return END; }
<<EOF>>         { return 0; }
[ \t\n]+        { }

%%
