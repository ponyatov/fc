#pragma once

/// @defgroup libc libc
/// @{
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/// @}

/// @defgroup stl stl
/// @ingroup libc
/// @{
#include <string>
#include <map>
#include <vector>
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
/// @brief narrow types for MCUs
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
/// @brief & @ref vm registers
/// @ingroup vm
/// @{
extern byte M[Msz];  ///< main memory
extern addr Cp;      ///< compiler pointer
extern addr Ip;      ///< instruction pointer
extern addr R[Rsz];  ///< return stack
extern cell D[Dsz];  ///< data stack

enum class Op;
/// @brief bytecode memory header (first bytes of @ref M)
struct HEAD {
    Op _jmp;      ///< @brief @ref entry jump
    addr entry;   ///< @brief = @ref Ip : program entry point
    addr latest;  ///< @brief Field Area of latest item in vocabulary
                  ///<        (zero if no vocabulary used)
    addr free;    ///< @brief heap = @ref Cp : free memory blocks list
    addr used;    ///< @brief heap: used memory blocks list
};

extern void head_sync();  ///< syncronize @ref vm registers -> @ref HEAD

/// @}

/// @defgroup allocator allocator
/// @ingroup flang
/// @brief dynamic memory allocator
/// @{

/// header for memory blocks allocated at top of @ref M
struct Alloc {
    addr next;  ///< next block in chain
    addr size;  ///< block size, bytes
    addr ref;   ///< ref counter (0xFFFF for locked blocks)
};

/// @}

/// @defgroup cmd cmd
/// @brief command set
/// @ingroup vm
/// @{

/// @brief command opcode
enum class Op {
    nop,   ///< `( -- )` do nothing
    halt,  ///< `( -- )` stop process
    jmp,   ///< `( -- )` unconditional jump
    jnz,   ///< `( -- )` conditional jump
    call,  ///< `(R: -- addr )` nested call
    ret,   ///< `(R: addr -- )` return from nested call
};

/// @brief opcode names table
extern char *opName[];

/// @}

/// @defgroup compiler compiler
/// @{

extern bool compile;  ///< compiling state marker
extern addr C(Op);    ///< compile @ref Op
extern addr C(cell);  ///< compile @ref cell

/// labels table
extern std::map<std::string, addr> label;
/// forward references table
extern std::map<std::string, std::vector<addr>> forward;

extern addr lookup(char *label);  ///< lookup label in symbol table

/// @}

/// @defgroup parser parser
/// @brief syntax parser
/// @ingroup flang
/// @{
extern int yylex();              ///< lexer
extern char *yytext;             ///< token value
extern int yylineno;             ///< current line number
extern char *yyfile;             ///< current file name
extern FILE *yyin;               ///< current file file handler
extern int yyparse();            ///< parser
extern void yyerror(char *msg);  ///< syntax error callback
#include "fc.yacc.hpp"           //   generated tokens definitions
/// @}
