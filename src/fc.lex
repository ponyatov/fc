%{
#include "fc.hpp"
char* yyfile = nullptr;
%}

%option noyywrap yylineno

%%
"//"[^\n]*  {}              // line comment
.           {yyerror("");}  // lexer error on any undetected char
