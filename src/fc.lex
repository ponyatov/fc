%{
#include "fc.hpp"
char* yyfile = nullptr;
%}

%option noyywrap yylineno

%x LINECOMMENT
%x BLOCKCOMMENT

%%
^"#!"               {BEGIN(LINECOMMENT);}   // shebang
"//"                {BEGIN(LINECOMMENT);}   // line comment
<LINECOMMENT>"\n"   {BEGIN(INITIAL);}
<LINECOMMENT>.      {}
"/*"                {BEGIN(BLOCKCOMMENT);} // block comment
<BLOCKCOMMENT>"*/"  {BEGIN(INITIAL);}
<BLOCKCOMMENT>.     {}

"nop"           CMD(CMD0,Op::nop )
"halt"          CMD(CMD0,Op::halt)

[ \t\r\n]+      {}              // drop spaces
.               {yyerror("");}  // lexer error on any undetected char
