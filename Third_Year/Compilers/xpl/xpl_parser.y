%{
// $Id: xpl_parser.y,v 1.13 2017/05/05 18:22:17 ist180967 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
	int                  				i;				/* integer value */
	double								d; 				/* double value - real in xpl */
	std::string          				*s;				/* symbol name or string literal */
	cdk::basic_node      				*node;			/* node pointer */
	cdk::sequence_node  			  	*sequence;
	cdk::expression_node 				*expression; 	/* expression nodes */
	cdk::lvalue_node     				*lvalue;
	basic_type							*type;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING
%token <expression> tNULL
%token tWHILE tIF tPRINTLN tRETURN tSTOP tNEXT tSWEEP tPUBLIC tPROCEDURE tUSE
%token tTYPEINT tTYPESTRING tTYPEDOUBLE

%nonassoc tIFX
%nonassoc tELSE
%nonassoc tELIF

%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tEQ tNE
%left '>' '<' tGE tLE
%left '+' '-'
%left '*' '/' '%'
%left '['

%nonassoc tUNARY

%type <s> literalString
%type <type> type;

%type <node> stmt elseconds sweeploop
%type <sequence> list fundeclargs    funcallargs
%type <expression> expr funcall  funcallarg
%type <lvalue> leftval

%type <sequence>	decls args vardecls 
%type <node>		decl  arg  vardecl  

%type<expression> literal

%type <node> block functions
%type <node> file

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file        		: decls                      										{ YYPARSE_PARAM->ast($1); }
            		|                                 									{ YYPARSE_PARAM->ast(new cdk::nil_node(LINE)); }
            		;

decls   			: decl                       										{ $$ = new cdk::sequence_node(LINE, $1); 		}
            		| decls decl          												{ $$ = new cdk::sequence_node(LINE, $2, $1); 	}
            		;


decl				: functions															{ $$ = $1; }
					| vardecl 															{ $$ = $1; }					
					;

vardecls    		: vardecl                          									{ $$ = new cdk::sequence_node(LINE, $1); 		}
            		| vardecls vardecl                 									{ $$ = new cdk::sequence_node(LINE, $2, $1); 	}
            		;

vardecl 			: type tIDENTIFIER ';'												{ $$ = new xpl::variable_decl_node(LINE, $1, $2, nullptr, true,  false, false); 	}
					| tPUBLIC type tIDENTIFIER ';'										{ $$ = new xpl::variable_decl_node(LINE, $2, $3, nullptr, false, false, false);	}
					| tUSE type tIDENTIFIER ';'											{ $$ = new xpl::variable_decl_node(LINE, $2, $3, nullptr, true,  true,  false); 	}
					| type tIDENTIFIER '=' expr ';'										{ $$ = new xpl::variable_decl_node(LINE, $1, $2, $4,   true,  false, false);  	}
					| tPUBLIC type tIDENTIFIER '=' expr ';'								{ $$ = new xpl::variable_decl_node(LINE, $2, $3, $5,   false, false, false); 	}
					;


functions 			: tPUBLIC type tIDENTIFIER '(' fundeclargs ')'						{ $$ = new xpl::function_decl_node(LINE, false, false, $2, $3, $5); 	}
					| type tIDENTIFIER '(' fundeclargs ')'								{ $$ = new xpl::function_decl_node(LINE, true, 	false, $1, $2, $4); 	}
					| tUSE type tIDENTIFIER '(' fundeclargs ')'							{ $$ = new xpl::function_decl_node(LINE, true, 	true,  $2, $3, $5); 	}
					| tPUBLIC tPROCEDURE tIDENTIFIER '(' fundeclargs ')' 				{ $$ = new xpl::function_decl_node(LINE, false, false, new basic_type(0, basic_type::TYPE_VOID), $3, $5); }
					| tPROCEDURE tIDENTIFIER '(' fundeclargs ')' 						{ $$ = new xpl::function_decl_node(LINE, true, false, new basic_type(0, basic_type::TYPE_VOID), $2, $4); }

					| tPUBLIC type tIDENTIFIER '(' fundeclargs ')' '=' literal 	block	{ $$ = new xpl::function_def_node(LINE, false, $2, $3, $5,$8, $9); 	}
					| tPUBLIC type tIDENTIFIER '(' fundeclargs ')'	block				{ $$ = new xpl::function_def_node(LINE, false, $2, $3, $5, nullptr, $7); 	}
					| type tIDENTIFIER '(' fundeclargs ')' '=' literal	block			{ $$ = new xpl::function_def_node(LINE, true, $1, $2, $4, $7, $8); 	}
					| type tIDENTIFIER '(' fundeclargs ')'	block						{ $$ = new xpl::function_def_node(LINE, true, $1, $2, $4, nullptr, $6); 	}
					| tPUBLIC tPROCEDURE tIDENTIFIER '(' fundeclargs ')' block			{ $$ = new xpl::function_def_node(LINE, false, new basic_type(0, basic_type::TYPE_VOID), $3, $5, nullptr, $7); }
					| tPROCEDURE tIDENTIFIER '(' fundeclargs ')' block					{ $$ = new xpl::function_def_node(LINE, true, new basic_type(0, basic_type::TYPE_VOID), $2, $4, nullptr, $6); }
					;

fundeclargs			: args																{ $$ = $1;		}
					|																	{ $$ = new cdk::sequence_node(LINE);	}
					;

args				: arg																{ $$ = new cdk::sequence_node(LINE, $1);		}
					| args ',' arg														{ $$ = new cdk::sequence_node(LINE, $3, $1);	}
					;

arg					: type tIDENTIFIER                 									{ $$ = new xpl::variable_decl_node(LINE, $1, $2, NULL, true, false, true); };
					;

type				: tTYPEINT															{ $$ = new basic_type(4, basic_type::TYPE_INT); 	}
					| tTYPESTRING														{ $$ = new basic_type(4, basic_type::TYPE_STRING); 	}
					| tTYPEDOUBLE														{ $$ = new basic_type(8, basic_type::TYPE_DOUBLE); 	}
					| '[' type ']'														{ $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $2; }
					;

literal   			: tINTEGER                         									{ $$ = new cdk::integer_node(LINE, $1); }
					| tDOUBLE                          									{ $$ = new cdk::double_node(LINE, $1); 	}
					| literalString														{ $$ = new cdk::string_node(LINE, $1);	}
					| tNULL 															{ $$ = new xpl::null_node(LINE); }
					;

literalString		: tSTRING															{ $$ = $1;	}
					| literalString tSTRING												{ $$ = new std::string(*$1 + *$2); delete $1; delete $2;	}
					;

block 				: '{' vardecls list '}'          									{ $$ = new xpl::block_node(LINE, $2, $3); 		}
            		| '{' vardecls '}'                									{ $$ = new xpl::block_node(LINE, $2, new cdk::sequence_node(LINE)); 	}
            		| '{' list '}'                   									{ $$ = new xpl::block_node(LINE, new cdk::sequence_node(LINE), $2); 	}
            		| '{' '}'                          									{ $$ = new xpl::block_node(LINE, new cdk::sequence_node(LINE), new cdk::sequence_node(LINE)); 	}
            		;
	
list            	: stmt	     														{ $$ = new cdk::sequence_node(LINE, $1); 		}
					| list stmt 														{ $$ = new cdk::sequence_node(LINE, $2, $1); 	}
					;

stmt 				: expr ';'                         									{ $$ = new xpl::evaluation_node(LINE, $1); }
					| expr "!"															{ $$ = new xpl::print_node(LINE, $1); }
					| expr tPRINTLN														{ $$ = new xpl::println_node(LINE, $1);	}
					| tWHILE '(' expr ')' stmt         									{ $$ = new xpl::while_node(LINE, $3, $5); }
					| sweeploop 														{ $$ = $1; }
					| tNEXT																{ $$ = new xpl::next_node(LINE); }
					| tSTOP																{ $$ = new xpl::stop_node(LINE); }
					| tRETURN															{ $$ = new xpl::return_node(LINE); }
					| tIF 	'(' expr ')' stmt %prec tIFX								{ $$ = new xpl::if_node(LINE, $3, $5); }
					| tIF 	'(' expr ')' stmt elseconds									{ $$ = new xpl::if_else_node(LINE, $3, $5, $6); }
					| block 	                     									{ $$ = $1; }
					;


sweeploop 			: tSWEEP '+' '(' leftval ':' expr ':' expr ')' stmt 				{ $$ = new xpl::sweep_plus_node(LINE, $4, $6, $8, new cdk::integer_node(LINE, 1), $10);	 }
					| tSWEEP '-' '(' leftval ':' expr ':' expr ')' stmt 				{ $$ = new xpl::sweep_minus_node(LINE, $4, $6, $8, new cdk::integer_node(LINE, 1), $10);	 }
					| tSWEEP '+' '(' leftval ':' expr ':' expr ':' expr ')' stmt 		{ $$ = new xpl::sweep_plus_node(LINE, $4, $6, $8, $10, $12);	 	}
					| tSWEEP '-' '(' leftval ':' expr ':' expr ':' expr ')' stmt 		{ $$ = new xpl::sweep_minus_node(LINE, $4, $6, $8, $10, $12);	}
					;

elseconds 			: tELSE stmt 														{ $$ = $2; }
					| tELIF '(' expr ')' stmt %prec tIFX								{ $$ = new xpl::if_node(LINE, $3, $5); }
					| tELIF '(' expr ')' stmt elseconds									{ $$ = new xpl::if_else_node(LINE, $3, $5, $6); }
					;


expr 				: literal                											{ $$ = $1; }
					| '-' expr %prec tUNARY   											{ $$ = new cdk::neg_node(LINE, $2); }
					| '+' expr %prec tUNARY   											{ $$ = new xpl::identity_node(LINE, $2); }
					| '~' expr 															{ $$ = new cdk::not_node(LINE, $2);}
					| expr '+' expr	         											{ $$ = new cdk::add_node(LINE, $1, $3); }
					| expr '-' expr	         											{ $$ = new cdk::sub_node(LINE, $1, $3); }
					| expr '*' expr	         											{ $$ = new cdk::mul_node(LINE, $1, $3); }
					| expr '/' expr	         											{ $$ = new cdk::div_node(LINE, $1, $3); }
					| expr '%' expr	         											{ $$ = new cdk::mod_node(LINE, $1, $3); }
					| expr '<' expr	                    								{ $$ = new cdk::lt_node(LINE, $1, $3); }
					| expr '>' expr	         											{ $$ = new cdk::gt_node(LINE, $1, $3); }
					| expr tGE expr	                    								{ $$ = new cdk::ge_node(LINE, $1, $3); }
					| expr tLE expr                     								{ $$ = new cdk::le_node(LINE, $1, $3); }
					| expr tNE expr	                    								{ $$ = new cdk::ne_node(LINE, $1, $3); }
					| expr tEQ expr	                    								{ $$ = new cdk::eq_node(LINE, $1, $3); }
					| expr '&' expr 													{ $$ = new cdk::and_node(LINE, $1, $3); }
					| expr '|' expr 													{ $$ = new cdk::or_node(LINE, $1, $3); }
					| '(' expr ')'                      								{ $$ = $2; }
					| '[' expr ']'                      								{ $$ = new xpl::mem_alloc_node(LINE, $2); }
					| leftval                              								{ $$ = new cdk::rvalue_node(LINE, $1); }  //FIXME
					| leftval '=' expr                     								{ $$ = new cdk::assignment_node(LINE, $1, $3); }
					| leftval '?' 														{ $$ = new xpl::mem_address_node(LINE, $1);}
					| funcall									                        { $$ = $1; }
					| '@' 																{ $$ = new xpl::read_node(LINE);}
					;

funcall 			: tIDENTIFIER '(' ')' 												{ $$ = new xpl::function_call_node(LINE, $1, NULL); }
					| tIDENTIFIER '(' funcallargs ')' 									{ $$ = new xpl::function_call_node(LINE, $1, $3); 	}
					;

funcallargs 		: funcallarg 														{ $$ = new cdk::sequence_node(LINE, $1);		}
					| funcallargs ',' funcallarg 										{ $$ = new cdk::sequence_node(LINE, $3, $1);	}

funcallarg 			: expr 																{ $$ = $1; }
					;

leftval 			: tIDENTIFIER                        								{ $$ = new cdk::identifier_node(LINE, $1); }
					| expr '[' expr ']'												{ $$ = new xpl::indexing_node(LINE, $1, $3);}
					;

%%
