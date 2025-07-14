/** @file
    @brief Linux-hosted Virtual Machine */

#include "fc.hpp"

int main(int argc, char *argv[]) {
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {
        arg(i, argv[i]);
        yyfile = argv[i];
        assert(yyin = fopen(yyfile, "r"));
        yyparse();
        fclose(yyin);
        yyfile = nullptr;
    }
    return 0;
}

void arg(int argc, char *argv) {  //
    fprintf(stderr, "arg[%i] = <%s>\n", argc, argv);
}

char *opName[] = {"nop", "halt", "jmp", "jnz", "call", "ret"};

byte M[Msz];

addr Cp = 0, Ip = 0;

bool compile = true;  // default: start in @ref compile state

addr C(Op op) {
    *(Op *)(&M[Cp]) = op;
    return Cp += sizeof(op);
}

addr C(cell n) {
    *(cell *)(&M[Cp]) = n;
    return Cp += sizeof(n);
}
