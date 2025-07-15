/** @file
    @brief lexer */
%{
#include "fc.hpp"
char* yyfile = nullptr;
%}

%option noyywrap yylineno

%x LINECOMMENT
%x BLOCKCOMMENT

s     [-\+]
n     [0-9]
alpha [a-zA-Z_]
alnum [a-zA-Z_]

%%
^"#!"               {BEGIN(LINECOMMENT);}   // shebang
"//"                {BEGIN(LINECOMMENT);}   // line comment
<LINECOMMENT>"\n"   {BEGIN(INITIAL);}
<LINECOMMENT>.      {}
"/*"                {BEGIN(BLOCKCOMMENT);} // block comment
<BLOCKCOMMENT>"*/"  {BEGIN(INITIAL);}
<BLOCKCOMMENT>.     {}

"nop"           { yylval.cmd = Op::nop ; return CMD0; }
"halt"          { yylval.cmd = Op::halt; return CMD0; }
"jmp"           { yylval.cmd = Op::jmp ; return CMD1; }
"jnz"           { yylval.cmd = Op::jnz ; return CMD1; }
"call"          { yylval.cmd = Op::call; return CMD1; }
"ret"           { yylval.cmd = Op::ret ; return CMD0; }

{s}?{n}+        { yylval.n = atoi(yytext); return INT; }

{alpha}{alnum}* { yylval.s = new std::string(yytext); return ID; }

[ \t\r\n]+      {}              // drop spaces
.               {yyerror("");}  // lexer error on any undetected char
