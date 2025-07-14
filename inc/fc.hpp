#pragma once

/// @defgroup libc libc
/// @{
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/// @}

/// @defgroup main main
/// @ingroup libc
/// @{
extern int main(int argc, char *argv[]);
extern void arg(int argc, char *argv);
/// @}

/// @defgroup flang F
/// @brief tiny language for embedded devices (Cortex-M0..7, RISC-V, Xtensa)

/// @defgroup parser parser
/// @brief syntax parser
/// @ingroup flang
/// @{
extern int yylex();
extern int yylineno;
extern char *yytext;
extern char *yyfile;
extern FILE *yyin;
extern int yyparse();
extern void yyerror(char *msg);
#include "fc.yacc.hpp"
/// @}
