%{
#include "fc.hpp"
%}

%defines %union { char c; char* s; int n; float f; }

%%
syntax:

%%
void yyerror(char *msg) {
    fprintf(stderr, "\n\n%s:%i %s [%s]\n\n", yyfile, yylineno, msg, yytext);
    exit(-1);
}
