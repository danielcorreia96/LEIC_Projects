%option c++ yyclass="xpl_scanner" outfile="xpl_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{
/* $Id: xpl_scanner.l,v 1.12 2017/05/05 19:54:57 ist180967 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "xpl_scanner.h"
#include "xpl_parser.tab.h"

// don't change this
#define yyerror LexerError
%}

HEX_DIGIT [0-9a-fA-F]


%x X_STRING X_COMMENT X_SPECIAL_STRING X_SPECIAL_ZERO X_IGNORE
%%

">="                   	return tGE;
"<="                   	return tLE;
"=="                   	return tEQ;
"!="                   	return tNE;

"while"                	return tWHILE;
"if"                   	return tIF;
"elsif"					return tELIF;
"else"                 	return tELSE;
"sweep"					return tSWEEP;
"procedure" 			return tPROCEDURE;

"stop"					return tSTOP;
"next"					return tNEXT;
"return"				return tRETURN;

"!!"					return tPRINTLN;

"null" 					return tNULL;
"use" 					return tUSE;
"public"      			return tPUBLIC;
"int"         			return tTYPEINT;
"string"      			return tTYPESTRING;
"real"        			return tTYPEDOUBLE;

[A-Za-z_][A-Za-z0-9_]* 	/*std::cout << "yacc received this identifier: " << *yytext << std::endl; */ yylval.s = new std::string(yytext); return tIDENTIFIER;

[-+*/~%=<>,;:!?@&|[\](){}]     /*std::cout << "yacc received this operator: " << *yytext << std::endl; */ return *yytext;

[ \t\n]+               	; /* ignore whitespace */

\"                     	yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"           	/*std::cout << "yacc received this string: " << *yylval.s << std::endl;*/ yy_pop_state(); return tSTRING;
<X_STRING>\\\"         	*yylval.s += yytext + 1;
<X_STRING>\\			yy_push_state(X_SPECIAL_STRING);
<X_STRING>\\0 			/* std::cout << "goto special zero state" << std::endl; */ yy_push_state(X_SPECIAL_ZERO);
<X_STRING>.            	*yylval.s += yytext;	
<X_STRING>\n           	yyerror("newline in string");

<X_SPECIAL_STRING>n  						yy_pop_state(); *yylval.s += std::string(1, 10); /* LF - NL line feed, newline */
<X_SPECIAL_STRING>r 						yy_pop_state(); *yylval.s += std::string(1, 13); /* CR - carriage return */
<X_SPECIAL_STRING>t 						yy_pop_state(); *yylval.s += std::string(1, 9); /* HT - horizontal tab */
<X_SPECIAL_STRING>[\"\\]					yy_pop_state(); *yylval.s += std::string(1,(int)*yytext); /* aspas e duas barras */
<X_SPECIAL_STRING>{HEX_DIGIT}{1,2} 			yy_pop_state(); *yylval.s += std::string(1, strtol(yytext, nullptr, 16)); /* convert hex number to ASCII code and then to string */
<X_SPECIAL_STRING>.|\n 						yyerror("Unknown special character in string");

<X_SPECIAL_ZERO>{HEX_DIGIT}          		yy_pop_state(); *yylval.s += std::string(1, strtol(yytext, nullptr, 16)); 
<X_SPECIAL_ZERO>. 							yy_push_state(X_IGNORE);

<X_IGNORE>\" 								yy_pop_state(); yy_pop_state(); yy_pop_state(); /* std::cout << "yacc terminated this string: " << *yylval.s << std::endl; */ return tSTRING;
<X_IGNORE>\\\"                              ;
<X_IGNORE>\\\\                              ;
<X_IGNORE>. 								;

"/*"					yy_push_state(X_COMMENT);
<X_COMMENT>"/*"			yy_push_state(X_COMMENT);
<X_COMMENT>"*/"			yy_pop_state();
<X_COMMENT>.|\n 		;


"//".*$					; /* ignore oneline comments */

[0-9]+([eE][+-]?[0-9]+) 				yylval.d = strtod(yytext, nullptr); if(errno == ERANGE) yyerror("Overflow ocurred!"); /* std::cout << "yacc received this double: " << yylval.d << std::endl; */ return tDOUBLE;
[0-9]+"."[0-9]*([eE][+-]?[0-9]+)? 		yylval.d = strtod(yytext, nullptr); if(errno == ERANGE) yyerror("Overflow ocurred!"); /* std::cout << "yacc received this double: " << yylval.d << std::endl; */ return tDOUBLE;
[0-9]*"."[0-9]+([eE][+-]?[0-9]+)? 		yylval.d = strtod(yytext, nullptr); if(errno == ERANGE) yyerror("Overflow ocurred!"); /* std::cout << "yacc received this double: " << yylval.d << std::endl; */ return tDOUBLE;
"0x"{HEX_DIGIT}+ 						yylval.i = strtol(yytext, nullptr, 16); if(errno == ERANGE) yyerror("Hex integer overflow!"); /* std::cout << "yacc received this hex integer: " << yylval.i << std::endl; */ return tINTEGER;
0|[1-9][0-9]*          					yylval.i = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("Normal integer overflow!"); /* std::cout << "yacc received this normal integer: " << yylval.i << std::endl; */ return tINTEGER;

.                      yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int xpl_scanner::yywrap() { return 1; }
