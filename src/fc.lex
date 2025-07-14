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

"nop"           { yylval.cmd0 = Op::nop ; return CMD0; }
"halt"          { yylval.cmd0 = Op::halt; return CMD0; }

[ \t\r\n]+      {}              // drop spaces
.               {yyerror("");}  // lexer error on any undetected char
