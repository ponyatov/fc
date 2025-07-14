#pragma once

/// @defgroup libc libc
/// @{
#include <stdint.h>
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

/// @defgroup vm vm
/// @ingroup flang
/// @brief FORTH-like Virtual Machine ([bytecode](md_doc_bytecode.html)
/// interpreter)

/// @defgroup types types
/// @details These types were especially narrowed for using in low- and mid-end
/// microcontrollers:
/// - 16-bit math is inconvenient for most cases, so we use `i32` @ref cell for
/// stack & ops
/// - `float16` not included in C/C++ standards until C++23, so `f32` @ref fcell
/// has the same size as @ref cell, and shares @ref D ata stack
/// - most MCUs have 128K SRAM and less (down to 2..4K in most cheapest), so
/// `u16` @ref addr esses is the best
/// @ingroup vm
/// @{
typedef uint8_t byte;   ///< single byte
typedef uint16_t addr;  ///< virtual memory address
typedef int32_t cell;   ///< signed integer
typedef float fcell;    ///< floating point number
static_assert(sizeof(cell) == sizeof(fcell));
/// @}

/// @defgroup config config
/// @ingroup vm
/// @{
const addr Msz = (uint16_t)0x10000;  ///< @ref M emory size, bytes
const addr Rsz = (uint16_t)0x100;  ///< @ref R eturn stack size, max call depth
const byte Dsz = (uint8_t)0x10;    ///< @ref D ata stack size, @ref cell[]s
/// @}

/// @defgroup memory memory
/// @ingroup vm
/// @{
extern byte M[Msz];  ///< main memory
extern addr R[Rsz];  ///< return stack
extern cell D[Dsz];  ///< data stack
/// @}

/// @defgroup cmd cmd
/// @ingroup vm
/// @{

enum class Op {
    nop = 0x00,
    halt = 0xFF,
};

/// @}

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
