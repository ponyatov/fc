%{
#include "fc.hpp"
%}

%defines %union { char c; char* s; int n; float f; Op cmd0; }

%token<cmd0> CMD0
%%
syntax: | syntax cmd ;

cmd: CMD0 ;

%%
void yyerror(char *msg) {
    fprintf(stderr, "\n\n%s:%i %s [%s]\n\n", yyfile, yylineno, msg, yytext);
    exit(-1);
}
