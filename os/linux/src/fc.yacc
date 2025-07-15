/** @file
    @brief parser & syntax-directed @ref compiler */
%{
#include "fc.hpp"
%}

%defines %union { char c; std::string *s; int n; float f; Op cmd; }

%token<cmd> CMD0 CMD1
%token<n> INT OCT HEX BIN
%token<s> ID

%type<n> arg

%%
syntax: | syntax cmd ;

cmd:
      CMD0      { fprintf(stderr,"%.4X:\tcmd0: %s\n"   ,
                    Cp,opName[(byte)$1]                );
                    C($1);                             }
    | CMD1 arg  { fprintf(stderr,"%.4X:\tcmd1: %s %x\n",
                    Cp,opName[(byte)$1], $2            );
                    C($1); C($2);                      }
    | CMD1 ID   { fprintf(stderr,"%.4X:\tcmd1: %s %s\n",
                    Cp,opName[(byte)$1], $2.c_str());
                    C($1); C(lookup($2)); }
;

arg: INT | OCT | HEX | BIN

%%
void yyerror(char *msg) {
    fprintf(stderr, "\n\n%s:%i %s [%s]\n\n", yyfile, yylineno, msg, yytext);
    exit(-1);
}
