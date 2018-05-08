/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20150711

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "xpl_parser.y"
/* $Id: xpl_parser.y,v 1.13 2017/05/05 18:22:17 ist180967 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 14 "xpl_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	int                  				i;				/* integer value */
	double								d; 				/* double value - real in xpl */
	std::string          				*s;				/* symbol name or string literal */
	cdk::basic_node      				*node;			/* node pointer */
	cdk::sequence_node  			  	*sequence;
	cdk::expression_node 				*expression; 	/* expression nodes */
	cdk::lvalue_node     				*lvalue;
	basic_type							*type;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 65 "xpl_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 52 "xpl_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tDOUBLE 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tNULL 261
#define tWHILE 262
#define tIF 263
#define tPRINTLN 264
#define tRETURN 265
#define tSTOP 266
#define tNEXT 267
#define tSWEEP 268
#define tPUBLIC 269
#define tPROCEDURE 270
#define tUSE 271
#define tTYPEINT 272
#define tTYPESTRING 273
#define tTYPEDOUBLE 274
#define tIFX 275
#define tELSE 276
#define tELIF 277
#define tEQ 278
#define tNE 279
#define tGE 280
#define tLE 281
#define tUNARY 282
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   13,   13,   16,   16,   15,   15,   18,   18,
   18,   18,   18,   21,   21,   21,   21,   21,   21,   21,
   21,   21,   21,   21,    7,    7,   14,   14,   17,    2,
    2,    2,    2,   19,   19,   19,   19,    1,    1,   20,
   20,   20,   20,    6,    6,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    5,    5,    5,    5,
    4,    4,    4,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,   10,   10,    8,
    8,   11,   12,   12,
};
static const YYINT yylen[] = {                            2,
    1,    0,    1,    2,    1,    1,    1,    2,    3,    4,
    4,    5,    6,    6,    5,    6,    6,    5,    9,    7,
    8,    6,    7,    6,    1,    0,    1,    3,    2,    1,
    1,    1,    3,    1,    1,    1,    1,    1,    2,    4,
    3,    3,    2,    1,    2,    2,    2,    2,    5,    1,
    1,    1,    1,    5,    6,    1,   10,   10,   12,   12,
    2,    5,    6,    1,    2,    2,    2,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    1,    3,    2,    1,    1,    3,    4,    1,
    3,    1,    1,    4,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,   30,   31,   32,    0,    0,    0,    0,
    3,    6,    5,    0,    0,    0,    0,    0,    0,    4,
    0,    0,    0,    0,   33,    0,    9,    0,    0,    0,
   10,    0,    0,    0,    0,   27,   11,    0,   34,   35,
    0,   38,   37,    0,    0,    0,    0,    0,   87,    0,
    0,   86,    0,   64,    0,    0,    0,    0,   29,    0,
    0,    0,    0,    0,   66,   65,    0,    0,   39,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   12,    0,   85,    0,    0,   13,    0,
    0,   24,   28,   16,   88,    0,    0,   90,   82,   81,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   22,   23,    0,   20,
    0,    0,   53,   52,   51,    0,    0,    0,    0,   43,
    0,   44,   50,    0,    0,    0,    7,   56,   89,    0,
   94,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   42,   45,   48,   46,   47,   41,    0,    8,   91,   21,
   19,    0,    0,    0,    0,    0,    0,   40,    0,    0,
    0,    0,    0,   49,    0,    0,    0,    0,    0,   55,
    0,    0,   61,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   57,    0,   58,    0,   63,
    0,    0,   59,   60,
};
static const YYINT yydgoto[] = {                          8,
   50,   33,  132,  180,  133,  134,   34,   96,  135,   52,
   98,   53,   10,   35,  136,   11,   36,   12,   54,  138,
   13,
};
static const YYINT yysindex[] = {                       -32,
  -51, -253,  -60,    0,    0,    0,  -60,    0, -243,  -32,
    0,    0,    0, -237, -217,   22, -213,  -23,  -25,    0,
   41,    8,  -60,  -22,    0, 1372,    0,  -60,  -60, 1372,
    0,  -60, -184,   44,   46,    0,    0,  -60,    0,    0,
   56,    0,    0, 1372, 1372, 1372, 1372, 1372,    0, -151,
  546,    0,   66,    0,   72,   73,  576,   79,    0,   15,
  -60,   83, 1287,  207,    0,    0,  613,  685,    0, 1372,
 1372, 1372, 1372, 1372, 1372, 1372, 1372, 1372, 1372, 1372,
 1372, 1372, 1372,    0, 1372,    0,  -59,   15,    0,  -58,
 1020,    0,    0,    0,    0,  -21,  934,    0,    0,    0,
  984,  207,  828,  828,   -4,   -4,   -4,   -4,   14,   14,
   39,   39,   39,  711,  934, -105,    0,    0, -105,    0,
   91,   97,    0,    0,    0,  105,  -60,  -60,  998,    0,
 -118,    0,    0, 1076,  173, 1043,    0,    0,    0, 1372,
    0,   15,   15, 1372, 1372,  111,  117, -117,  -96,  107,
    0,    0,    0,    0,    0,    0, 1107,    0,    0,    0,
    0,  722,  756, 1372, 1372,  128,  110,    0, 1343, 1343,
  934,   -6,   45,    0, -223, 1372, 1372, 1343,  130,    0,
  791,  821,    0, 1372, 1372, 1372,  858,  463,  510, 1343,
 1343, 1372, 1343, 1372, -223,    0,  884,    0,  895,    0,
 1343, 1343,    0,    0,
};
static const YYINT yyrindex[] = {                       176,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  177,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  132,    0,    0,    0,    0,  132,  132,    0,
    0,  132,    0,    0,  139,    0,    0,  132,    0,    0,
  -33,    0,    0,    0,    0,    0,    0,    0,    0,   35,
    0,    0,   74,    0,    0,    0,    0,    0,    0,    1,
    0,    0,    0,  476,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    7,   13,    0,   19,
    0,    0,    0,    0,    0,    0,   42,    0,    0,    0,
   30, 1035,  435,  437,  299,  368,  398,  405,  286,  331,
  102,  141,  263,    0,   -9,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  968,  968,    0, 1143,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1307,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0, 1193, 1051,   -5,    0,   55,  143,    0, 1508,    0,
   52,  -63,    0,    0,    0,  183,  133,  -70,    6,  -43,
    0,
};
#define YYTABLESIZE 1702
static const YYINT yytable[] = {                         93,
   18,  116,  119,   93,   93,   16,   15,   93,   93,   93,
   93,   93,   17,   93,   28,   19,   92,   38,   14,  139,
  137,   21,  140,   84,   93,   93,   93,   93,   93,   93,
    7,   84,   82,   27,   84,   26,   37,   80,   78,    7,
   79,   22,   81,  117,  118,   24,  120,   32,   84,   84,
   82,  176,  178,  179,   85,   80,   86,   93,    7,   93,
   81,   23,   80,   91,   91,  158,   31,   36,   30,   25,
   80,   36,   36,   80,   59,   36,   36,   36,   36,   36,
   29,   36,   92,   84,   60,   92,   83,   80,   80,   61,
   93,   18,   36,   36,   36,   63,   36,   15,  160,  161,
  172,  173,  177,   17,   83,   85,   83,   86,   69,   14,
   83,   83,   87,   88,   83,   83,   83,   83,   83,   90,
   83,  142,   80,   94,  143,   36,   85,   36,   86,   83,
  144,   83,   83,   83,   70,   83,  145,   91,   70,   70,
  150,  166,   70,   70,   70,   70,   70,  146,   70,  147,
  164,   39,   40,   80,   42,   43,  165,   36,   36,   70,
   70,   70,  167,   70,   83,   27,   83,   26,   37,  184,
   55,   56,   26,   71,   58,    2,    1,   71,   71,   25,
   62,   71,   71,   71,   71,   71,   31,   71,   30,  200,
  157,  159,   20,   93,   70,    0,    0,   83,   71,   71,
   71,    0,   71,    0,    0,  155,    0,    0,    0,   82,
   71,    4,    5,    6,   80,   78,    0,   79,   14,   81,
    4,    5,    6,    0,    0,   70,    0,    0,    0,    0,
   93,  154,   75,   71,   74,    0,    1,    2,    3,    4,
    5,    6,    0,   82,   93,   93,   93,   93,   80,   78,
    0,   79,    0,   81,   84,    0,    0,    0,    0,    0,
    0,    0,    0,   83,   71,    0,   75,    0,   74,   18,
   18,   18,   18,   18,   18,   15,   15,   15,   15,   15,
   15,   17,   17,   17,   17,   17,   17,   14,   14,   14,
   14,   14,   14,   80,    0,   72,   70,   83,   36,   72,
   72,    0,    0,   72,   72,   72,   72,   72,    0,   72,
    0,    0,   36,   36,   36,   36,    0,    0,   68,    0,
   72,   72,   72,   68,   72,    0,   68,    0,   68,   68,
   68,   74,    0,    0,    0,    0,   74,   83,    0,   74,
    0,    0,   74,   68,   68,   68,    0,   68,    0,    0,
    0,   83,   83,   83,   83,   72,   74,   74,   74,    0,
   74,    0,    0,   69,    0,   70,    0,    0,   69,    0,
    0,   69,    0,   69,   69,   69,    0,    0,   68,   70,
   70,   70,   70,    0,    0,    0,   72,    0,   69,   69,
   69,   74,   69,    0,    0,    0,    0,    0,    0,    0,
   73,    0,    0,    0,   71,   73,    0,    0,   73,   68,
    0,   73,    0,    0,    0,    0,    0,    0,   71,   71,
   71,   71,   74,   69,    0,   73,   73,   73,    0,   73,
   75,    0,    0,    0,    0,   75,  153,   76,   75,    0,
    0,   75,   76,    0,    0,   76,    0,    0,   76,    0,
   72,   73,   76,   77,   69,   75,   75,   75,    0,   75,
   73,    0,   76,   76,   76,    0,   76,   78,    0,   77,
    0,    0,   78,    0,   77,   78,    0,   77,   78,    0,
   77,    0,    0,    0,   72,   73,   76,   77,    0,    0,
   75,   73,   78,   78,   77,   77,    0,   76,    0,   82,
   71,    0,    0,  191,   80,   78,    0,   79,   67,   81,
    0,    0,    0,   67,    0,    0,   67,    0,    0,   67,
  192,   75,   75,    0,   74,    0,   72,   78,   76,   77,
    0,    0,    0,   67,   67,    0,    0,    0,    0,    0,
   72,   72,   72,   72,    0,    0,   82,   71,    0,   68,
  193,   80,   78,   83,   79,    0,   81,    0,   78,    0,
   77,    0,   74,   68,   68,   68,   68,  194,   67,   75,
    0,   74,    0,    0,    0,    0,   74,   74,   74,   74,
    0,    0,   82,   71,    0,    0,   70,   80,   78,    0,
   79,    0,   81,    0,   69,    0,    0,    0,    0,   67,
   83,    0,    0,    0,   84,   75,    0,   74,   69,   69,
   69,   69,   82,   71,    0,    0,    0,   80,   78,    0,
   79,    0,   81,    0,    0,    0,    0,    0,    0,    0,
    0,   73,    0,   70,   89,   75,   83,   74,    0,    0,
    0,    0,    0,    0,    0,   73,   73,   73,   73,   82,
   71,    0,    0,    0,   80,   78,    0,   79,    0,   81,
    0,   75,    0,    0,    0,    0,   83,    0,   76,   70,
    0,    0,   75,    0,   74,   75,   75,   75,   75,    0,
    0,    0,   76,   76,   76,   76,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   78,   70,
   77,    0,    0,   83,    0,   99,    0,    0,    0,    0,
    0,    0,   78,   78,   77,   77,    0,    0,    0,    0,
    0,   82,   71,    0,    0,  100,   80,   78,    0,   79,
    0,   81,    0,    0,    0,    0,   70,    0,    0,   67,
   72,   73,   76,   77,   75,    0,   74,   82,   71,    0,
    0,    0,   80,   78,    0,   79,    0,   81,   82,   71,
    0,    0,  169,   80,   78,    0,   79,    0,   81,    0,
   75,    0,   74,    0,    0,   83,    0,    0,    0,    0,
    0,   75,    0,   74,    0,    0,    0,   72,   73,   76,
   77,    0,   82,   71,    0,    0,  170,   80,   78,    0,
   79,   83,   81,  141,    0,    0,    0,    0,   70,    0,
    0,    0,   83,    0,    0,   75,    0,   74,    0,    0,
    0,    0,    0,   72,   73,   76,   77,   82,   71,    0,
    0,    0,   80,   78,   70,   79,    0,   81,    0,    0,
    0,    0,    0,    0,    0,   70,   83,    0,  185,    0,
   75,    0,   74,   72,   73,   76,   77,   82,   71,    0,
    0,    0,   80,   78,   82,   79,    0,   81,    0,   80,
   78,    0,   79,    0,   81,    0,    0,    0,  186,   70,
   75,   83,   74,    0,    0,    0,    0,   75,    0,   74,
   72,   73,   76,   77,   82,   71,    0,    0,  190,   80,
   78,    0,   79,    0,   81,    0,    0,    0,    0,    0,
    0,   83,    0,    0,   70,    0,    0,   75,   83,   74,
   82,   71,    0,    0,  201,   80,   78,    0,   79,    0,
   81,   82,   71,    0,    0,  202,   80,   78,    0,   79,
    0,   81,    0,   75,   70,   74,    0,    0,   83,    0,
    0,    0,    0,    0,   75,    0,   74,    0,    0,    0,
    0,    0,   72,   73,   76,   77,    0,    0,    0,    0,
   82,   71,    0,    0,   83,   80,   78,    0,   79,    0,
   81,   70,    0,    0,    0,   83,    0,    0,   72,   73,
   76,   77,    0,   75,    0,   74,    0,    0,    0,   72,
   73,   76,   77,    0,   83,   83,    0,   70,    0,   83,
   83,    0,   83,    0,   83,    0,    0,    0,   70,    0,
   82,   71,    0,    0,   83,   80,   78,   83,   79,   83,
   81,    0,    0,   72,   73,   76,   77,   48,    0,    0,
   45,    0,   46,   75,    0,   74,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   70,   83,   48,
    0,   49,   45,    0,   46,    0,    0,   79,   72,   73,
   76,   77,   79,    0,   83,   79,    0,    0,   79,    0,
    0,    0,   48,   49,    0,   45,    0,   46,  129,    0,
    0,   83,   79,   79,    0,    0,    0,    0,   72,   73,
   76,   77,    0,    0,    0,    0,   49,   76,   77,    0,
  129,    0,    0,    0,    0,   48,    0,    0,   45,    0,
   46,    0,    0,   44,    0,    0,    0,   79,    0,    0,
    0,    0,    0,  129,    0,   72,   73,   76,   77,   49,
    0,    0,   91,    0,  130,   44,   48,    0,    0,   45,
    0,   46,    0,    0,    0,    0,    0,    0,   79,    0,
    0,   72,   73,   76,   77,   91,   47,  156,   44,    0,
   49,    0,   72,   73,   76,   77,    0,    0,    0,    0,
    0,    0,   54,    0,  152,   54,    0,   54,    0,    0,
    0,    0,    9,   15,    0,   17,    0,   47,   91,   18,
  151,   44,    9,    0,    0,    0,   54,  152,    0,    0,
    0,   72,   73,   76,   77,    0,    0,    0,    0,  174,
  175,    0,    0,    0,    0,    0,    0,    0,  183,   91,
    0,  168,   44,   54,    0,    0,    0,    0,    0,    0,
  195,  196,    0,  198,    0,   83,   83,   83,   83,    0,
    0,  203,  204,    0,   39,   40,   41,   42,   43,    0,
    0,   72,   73,   76,   77,   54,    0,   54,   54,    4,
    5,    6,    0,    0,    0,    0,   39,   40,   41,   42,
   43,  121,  122,  131,  123,  124,  125,  126,  127,    0,
  128,    4,    5,    6,    0,    0,    0,    0,   79,   39,
   40,   41,   42,   43,  121,  122,    0,  123,  124,  125,
  126,  127,    0,  128,    4,    5,    6,    0,    0,  148,
  149,   18,    0,    0,    0,    0,   48,   95,  131,   45,
    0,   46,   39,   40,   41,   42,   43,  121,  122,    0,
  123,  124,  125,  126,    0,    0,   62,    0,    0,   62,
   49,   62,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   39,   40,   41,   42,   43,  121,  122,
   62,  123,  124,  125,  126,    0,    0,   47,    0,    0,
    0,    0,   48,    0,    0,   45,    0,   46,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   62,    0,   54,
   54,   54,   54,   54,   54,   54,   49,   54,   54,   54,
   54,   48,   44,    0,   45,    0,   46,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   62,
    0,   62,   62,   47,    0,   49,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   47,    0,    0,   91,    0,    0,   44,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   44,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   51,    0,    0,    0,   57,    0,    0,
    0,    0,    0,   39,   40,   41,   42,   43,    0,    0,
    0,   64,   65,   66,   67,   68,    0,    0,    0,    0,
    0,    0,    0,   62,   62,   62,   62,   62,   62,   62,
   97,   62,   62,   62,   62,    0,    0,  101,  102,  103,
  104,  105,  106,  107,  108,  109,  110,  111,  112,  113,
  114,    0,  115,    0,    0,    0,    0,    0,    0,   39,
   40,   41,   42,   43,  121,  122,    0,  123,  124,  125,
  126,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   39,   40,
   41,   42,   43,    0,    0,    0,   67,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   97,    0,    0,
    0,  162,  163,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  171,  171,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  181,  182,    0,    0,    0,    0,    0,
    0,  187,  188,  189,    0,    0,    0,    0,    0,  197,
    0,  199,
};
static const YYINT yycheck[] = {                         33,
    0,   61,   61,   37,   38,  259,    0,   41,   42,   43,
   44,   45,    0,   47,   40,  259,   60,   40,    0,   41,
   91,  259,   44,   33,   58,   59,   60,   61,   62,   63,
   91,   41,   37,   59,   44,   61,   59,   42,   43,   91,
   45,  259,   47,   87,   88,  259,   90,   40,   58,   59,
   37,   58,  276,  277,   61,   42,   63,   91,   91,   93,
   47,   40,   33,  123,  123,  136,   59,   33,   61,   93,
   41,   37,   38,   44,  259,   41,   42,   43,   44,   45,
   40,   47,   41,   93,   41,   44,   91,   58,   59,   44,
  124,   91,   58,   59,   60,   40,   62,   91,  142,  143,
  164,  165,   58,   91,   91,   61,   33,   63,  260,   91,
   37,   38,   41,   41,   41,   42,   43,   44,   45,   41,
   47,  116,   93,   41,  119,   91,   61,   93,   63,   91,
   40,   58,   59,   60,   33,   62,   40,  123,   37,   38,
  259,  259,   41,   42,   43,   44,   45,   43,   47,   45,
   40,  257,  258,  124,  260,  261,   40,  123,  124,   58,
   59,   60,  259,   62,   91,   59,   93,   61,   59,   40,
   28,   29,   41,   33,   32,    0,    0,   37,   38,   41,
   38,   41,   42,   43,   44,   45,   59,   47,   61,  195,
  136,  140,   10,   61,   93,   -1,   -1,  124,   58,   59,
   60,   -1,   62,   -1,   -1,   33,   -1,   -1,   -1,   37,
   38,  272,  273,  274,   42,   43,   -1,   45,  270,   47,
  272,  273,  274,   -1,   -1,  124,   -1,   -1,   -1,   -1,
  264,   59,   60,   93,   62,   -1,  269,  270,  271,  272,
  273,  274,   -1,   37,  278,  279,  280,  281,   42,   43,
   -1,   45,   -1,   47,  264,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   91,  124,   -1,   60,   -1,   62,  269,
  270,  271,  272,  273,  274,  269,  270,  271,  272,  273,
  274,  269,  270,  271,  272,  273,  274,  269,  270,  271,
  272,  273,  274,  264,   -1,   33,  124,   91,  264,   37,
   38,   -1,   -1,   41,   42,   43,   44,   45,   -1,   47,
   -1,   -1,  278,  279,  280,  281,   -1,   -1,   33,   -1,
   58,   59,   60,   38,   62,   -1,   41,   -1,   43,   44,
   45,   33,   -1,   -1,   -1,   -1,   38,  264,   -1,   41,
   -1,   -1,   44,   58,   59,   60,   -1,   62,   -1,   -1,
   -1,  278,  279,  280,  281,   93,   58,   59,   60,   -1,
   62,   -1,   -1,   33,   -1,  264,   -1,   -1,   38,   -1,
   -1,   41,   -1,   43,   44,   45,   -1,   -1,   93,  278,
  279,  280,  281,   -1,   -1,   -1,  124,   -1,   58,   59,
   60,   93,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   33,   -1,   -1,   -1,  264,   38,   -1,   -1,   41,  124,
   -1,   44,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,
  280,  281,  124,   93,   -1,   58,   59,   60,   -1,   62,
   33,   -1,   -1,   -1,   -1,   38,  264,   33,   41,   -1,
   -1,   44,   38,   -1,   -1,   41,   -1,   -1,   44,   -1,
  278,  279,  280,  281,  124,   58,   59,   60,   -1,   62,
   93,   -1,   58,   59,   60,   -1,   62,   33,   -1,   33,
   -1,   -1,   38,   -1,   38,   41,   -1,   41,   44,   -1,
   44,   -1,   -1,   -1,  278,  279,  280,  281,   -1,   -1,
   93,  124,   58,   59,   58,   59,   -1,   93,   -1,   37,
   38,   -1,   -1,   41,   42,   43,   -1,   45,   33,   47,
   -1,   -1,   -1,   38,   -1,   -1,   41,   -1,   -1,   44,
   58,  124,   60,   -1,   62,   -1,  264,   93,  124,   93,
   -1,   -1,   -1,   58,   59,   -1,   -1,   -1,   -1,   -1,
  278,  279,  280,  281,   -1,   -1,   37,   38,   -1,  264,
   41,   42,   43,   91,   45,   -1,   47,   -1,  124,   -1,
  124,   -1,  264,  278,  279,  280,  281,   58,   93,   60,
   -1,   62,   -1,   -1,   -1,   -1,  278,  279,  280,  281,
   -1,   -1,   37,   38,   -1,   -1,  124,   42,   43,   -1,
   45,   -1,   47,   -1,  264,   -1,   -1,   -1,   -1,  124,
   91,   -1,   -1,   -1,   59,   60,   -1,   62,  278,  279,
  280,  281,   37,   38,   -1,   -1,   -1,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  264,   -1,  124,   59,   60,   91,   62,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  278,  279,  280,  281,   37,
   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,  264,   -1,   -1,   -1,   -1,   91,   -1,  264,  124,
   -1,   -1,   60,   -1,   62,  278,  279,  280,  281,   -1,
   -1,   -1,  278,  279,  280,  281,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  264,  124,
  264,   -1,   -1,   91,   -1,   93,   -1,   -1,   -1,   -1,
   -1,   -1,  278,  279,  278,  279,   -1,   -1,   -1,   -1,
   -1,   37,   38,   -1,   -1,   41,   42,   43,   -1,   45,
   -1,   47,   -1,   -1,   -1,   -1,  124,   -1,   -1,  264,
  278,  279,  280,  281,   60,   -1,   62,   37,   38,   -1,
   -1,   -1,   42,   43,   -1,   45,   -1,   47,   37,   38,
   -1,   -1,   41,   42,   43,   -1,   45,   -1,   47,   -1,
   60,   -1,   62,   -1,   -1,   91,   -1,   -1,   -1,   -1,
   -1,   60,   -1,   62,   -1,   -1,   -1,  278,  279,  280,
  281,   -1,   37,   38,   -1,   -1,   41,   42,   43,   -1,
   45,   91,   47,   93,   -1,   -1,   -1,   -1,  124,   -1,
   -1,   -1,   91,   -1,   -1,   60,   -1,   62,   -1,   -1,
   -1,   -1,   -1,  278,  279,  280,  281,   37,   38,   -1,
   -1,   -1,   42,   43,  124,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   91,   -1,   58,   -1,
   60,   -1,   62,  278,  279,  280,  281,   37,   38,   -1,
   -1,   -1,   42,   43,   37,   45,   -1,   47,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   58,  124,
   60,   91,   62,   -1,   -1,   -1,   -1,   60,   -1,   62,
  278,  279,  280,  281,   37,   38,   -1,   -1,   41,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   91,   -1,   -1,  124,   -1,   -1,   60,   91,   62,
   37,   38,   -1,   -1,   41,   42,   43,   -1,   45,   -1,
   47,   37,   38,   -1,   -1,   41,   42,   43,   -1,   45,
   -1,   47,   -1,   60,  124,   62,   -1,   -1,   91,   -1,
   -1,   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,
   -1,   -1,  278,  279,  280,  281,   -1,   -1,   -1,   -1,
   37,   38,   -1,   -1,   91,   42,   43,   -1,   45,   -1,
   47,  124,   -1,   -1,   -1,   91,   -1,   -1,  278,  279,
  280,  281,   -1,   60,   -1,   62,   -1,   -1,   -1,  278,
  279,  280,  281,   -1,   37,   38,   -1,  124,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,  124,   -1,
   37,   38,   -1,   -1,   91,   42,   43,   60,   45,   62,
   47,   -1,   -1,  278,  279,  280,  281,   40,   -1,   -1,
   43,   -1,   45,   60,   -1,   62,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,   91,   40,
   -1,   64,   43,   -1,   45,   -1,   -1,   33,  278,  279,
  280,  281,   38,   -1,   91,   41,   -1,   -1,   44,   -1,
   -1,   -1,   40,   64,   -1,   43,   -1,   45,   91,   -1,
   -1,  124,   58,   59,   -1,   -1,   -1,   -1,  278,  279,
  280,  281,   -1,   -1,   -1,   -1,   64,  280,  281,   -1,
   91,   -1,   -1,   -1,   -1,   40,   -1,   -1,   43,   -1,
   45,   -1,   -1,  126,   -1,   -1,   -1,   93,   -1,   -1,
   -1,   -1,   -1,   91,   -1,  278,  279,  280,  281,   64,
   -1,   -1,  123,   -1,  125,  126,   40,   -1,   -1,   43,
   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,
   -1,  278,  279,  280,  281,  123,   91,  125,  126,   -1,
   64,   -1,  278,  279,  280,  281,   -1,   -1,   -1,   -1,
   -1,   -1,   40,   -1,  134,   43,   -1,   45,   -1,   -1,
   -1,   -1,    0,    1,   -1,    3,   -1,   91,  123,    7,
  125,  126,   10,   -1,   -1,   -1,   64,  157,   -1,   -1,
   -1,  278,  279,  280,  281,   -1,   -1,   -1,   -1,  169,
  170,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  178,  123,
   -1,  125,  126,   91,   -1,   -1,   -1,   -1,   -1,   -1,
  190,  191,   -1,  193,   -1,  278,  279,  280,  281,   -1,
   -1,  201,  202,   -1,  257,  258,  259,  260,  261,   -1,
   -1,  278,  279,  280,  281,  123,   -1,  125,  126,  272,
  273,  274,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,  263,   91,  265,  266,  267,  268,  269,   -1,
  271,  272,  273,  274,   -1,   -1,   -1,   -1,  264,  257,
  258,  259,  260,  261,  262,  263,   -1,  265,  266,  267,
  268,  269,   -1,  271,  272,  273,  274,   -1,   -1,  127,
  128,  129,   -1,   -1,   -1,   -1,   40,   41,  136,   43,
   -1,   45,  257,  258,  259,  260,  261,  262,  263,   -1,
  265,  266,  267,  268,   -1,   -1,   40,   -1,   -1,   43,
   64,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  257,  258,  259,  260,  261,  262,  263,
   64,  265,  266,  267,  268,   -1,   -1,   91,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   91,   -1,  257,
  258,  259,  260,  261,  262,  263,   64,  265,  266,  267,
  268,   40,  126,   -1,   43,   -1,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  123,
   -1,  125,  126,   91,   -1,   64,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   91,   -1,   -1,  123,   -1,   -1,  126,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   26,   -1,   -1,   -1,   30,   -1,   -1,
   -1,   -1,   -1,  257,  258,  259,  260,  261,   -1,   -1,
   -1,   44,   45,   46,   47,   48,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  257,  258,  259,  260,  261,  262,  263,
   63,  265,  266,  267,  268,   -1,   -1,   70,   71,   72,
   73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
   83,   -1,   85,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,  260,  261,  262,  263,   -1,  265,  266,  267,
  268,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,  261,   -1,   -1,   -1,  129,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  140,   -1,   -1,
   -1,  144,  145,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  164,  165,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  176,  177,   -1,   -1,   -1,   -1,   -1,
   -1,  184,  185,  186,   -1,   -1,   -1,   -1,   -1,  192,
   -1,  194,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 282
#define YYUNDFTOKEN 306
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,"':'","';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER",
"tDOUBLE","tIDENTIFIER","tSTRING","tNULL","tWHILE","tIF","tPRINTLN","tRETURN",
"tSTOP","tNEXT","tSWEEP","tPUBLIC","tPROCEDURE","tUSE","tTYPEINT","tTYPESTRING",
"tTYPEDOUBLE","tIFX","tELSE","tELIF","tEQ","tNE","tGE","tLE","tUNARY",0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : decls",
"file :",
"decls : decl",
"decls : decls decl",
"decl : functions",
"decl : vardecl",
"vardecls : vardecl",
"vardecls : vardecls vardecl",
"vardecl : type tIDENTIFIER ';'",
"vardecl : tPUBLIC type tIDENTIFIER ';'",
"vardecl : tUSE type tIDENTIFIER ';'",
"vardecl : type tIDENTIFIER '=' expr ';'",
"vardecl : tPUBLIC type tIDENTIFIER '=' expr ';'",
"functions : tPUBLIC type tIDENTIFIER '(' fundeclargs ')'",
"functions : type tIDENTIFIER '(' fundeclargs ')'",
"functions : tUSE type tIDENTIFIER '(' fundeclargs ')'",
"functions : tPUBLIC tPROCEDURE tIDENTIFIER '(' fundeclargs ')'",
"functions : tPROCEDURE tIDENTIFIER '(' fundeclargs ')'",
"functions : tPUBLIC type tIDENTIFIER '(' fundeclargs ')' '=' literal block",
"functions : tPUBLIC type tIDENTIFIER '(' fundeclargs ')' block",
"functions : type tIDENTIFIER '(' fundeclargs ')' '=' literal block",
"functions : type tIDENTIFIER '(' fundeclargs ')' block",
"functions : tPUBLIC tPROCEDURE tIDENTIFIER '(' fundeclargs ')' block",
"functions : tPROCEDURE tIDENTIFIER '(' fundeclargs ')' block",
"fundeclargs : args",
"fundeclargs :",
"args : arg",
"args : args ',' arg",
"arg : type tIDENTIFIER",
"type : tTYPEINT",
"type : tTYPESTRING",
"type : tTYPEDOUBLE",
"type : '[' type ']'",
"literal : tINTEGER",
"literal : tDOUBLE",
"literal : literalString",
"literal : tNULL",
"literalString : tSTRING",
"literalString : literalString tSTRING",
"block : '{' vardecls list '}'",
"block : '{' vardecls '}'",
"block : '{' list '}'",
"block : '{' '}'",
"list : stmt",
"list : list stmt",
"stmt : expr ';'",
"stmt : expr '!'",
"stmt : expr tPRINTLN",
"stmt : tWHILE '(' expr ')' stmt",
"stmt : sweeploop",
"stmt : tNEXT",
"stmt : tSTOP",
"stmt : tRETURN",
"stmt : tIF '(' expr ')' stmt",
"stmt : tIF '(' expr ')' stmt elseconds",
"stmt : block",
"sweeploop : tSWEEP '+' '(' leftval ':' expr ':' expr ')' stmt",
"sweeploop : tSWEEP '-' '(' leftval ':' expr ':' expr ')' stmt",
"sweeploop : tSWEEP '+' '(' leftval ':' expr ':' expr ':' expr ')' stmt",
"sweeploop : tSWEEP '-' '(' leftval ':' expr ':' expr ':' expr ')' stmt",
"elseconds : tELSE stmt",
"elseconds : tELIF '(' expr ')' stmt",
"elseconds : tELIF '(' expr ')' stmt elseconds",
"expr : literal",
"expr : '-' expr",
"expr : '+' expr",
"expr : '~' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : expr '&' expr",
"expr : expr '|' expr",
"expr : '(' expr ')'",
"expr : '[' expr ']'",
"expr : leftval",
"expr : leftval '=' expr",
"expr : leftval '?'",
"expr : funcall",
"expr : '@'",
"funcall : tIDENTIFIER '(' ')'",
"funcall : tIDENTIFIER '(' funcallargs ')'",
"funcallargs : funcallarg",
"funcallargs : funcallargs ',' funcallarg",
"funcallarg : expr",
"leftval : tIDENTIFIER",
"leftval : expr '[' expr ']'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 69 "xpl_parser.y"
	{ YYPARSE_PARAM->ast(yystack.l_mark[0].sequence); }
break;
case 2:
#line 70 "xpl_parser.y"
	{ YYPARSE_PARAM->ast(new cdk::nil_node(LINE)); }
break;
case 3:
#line 73 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); 		}
break;
case 4:
#line 74 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); 	}
break;
case 5:
#line 78 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 6:
#line 79 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 7:
#line 82 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); 		}
break;
case 8:
#line 83 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); 	}
break;
case 9:
#line 86 "xpl_parser.y"
	{ yyval.node = new xpl::variable_decl_node(LINE, yystack.l_mark[-2].type, yystack.l_mark[-1].s, nullptr, true,  false, false); 	}
break;
case 10:
#line 87 "xpl_parser.y"
	{ yyval.node = new xpl::variable_decl_node(LINE, yystack.l_mark[-2].type, yystack.l_mark[-1].s, nullptr, false, false, false);	}
break;
case 11:
#line 88 "xpl_parser.y"
	{ yyval.node = new xpl::variable_decl_node(LINE, yystack.l_mark[-2].type, yystack.l_mark[-1].s, nullptr, true,  true,  false); 	}
break;
case 12:
#line 89 "xpl_parser.y"
	{ yyval.node = new xpl::variable_decl_node(LINE, yystack.l_mark[-4].type, yystack.l_mark[-3].s, yystack.l_mark[-1].expression,   true,  false, false);  	}
break;
case 13:
#line 90 "xpl_parser.y"
	{ yyval.node = new xpl::variable_decl_node(LINE, yystack.l_mark[-4].type, yystack.l_mark[-3].s, yystack.l_mark[-1].expression,   false, false, false); 	}
break;
case 14:
#line 94 "xpl_parser.y"
	{ yyval.node = new xpl::function_decl_node(LINE, false, false, yystack.l_mark[-4].type, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); 	}
break;
case 15:
#line 95 "xpl_parser.y"
	{ yyval.node = new xpl::function_decl_node(LINE, true, 	false, yystack.l_mark[-4].type, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); 	}
break;
case 16:
#line 96 "xpl_parser.y"
	{ yyval.node = new xpl::function_decl_node(LINE, true, 	true,  yystack.l_mark[-4].type, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); 	}
break;
case 17:
#line 97 "xpl_parser.y"
	{ yyval.node = new xpl::function_decl_node(LINE, false, false, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); }
break;
case 18:
#line 98 "xpl_parser.y"
	{ yyval.node = new xpl::function_decl_node(LINE, true, false, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); }
break;
case 19:
#line 100 "xpl_parser.y"
	{ yyval.node = new xpl::function_def_node(LINE, false, yystack.l_mark[-7].type, yystack.l_mark[-6].s, yystack.l_mark[-4].sequence,yystack.l_mark[-1].expression, yystack.l_mark[0].node); 	}
break;
case 20:
#line 101 "xpl_parser.y"
	{ yyval.node = new xpl::function_def_node(LINE, false, yystack.l_mark[-5].type, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].node); 	}
break;
case 21:
#line 102 "xpl_parser.y"
	{ yyval.node = new xpl::function_def_node(LINE, true, yystack.l_mark[-7].type, yystack.l_mark[-6].s, yystack.l_mark[-4].sequence, yystack.l_mark[-1].expression, yystack.l_mark[0].node); 	}
break;
case 22:
#line 103 "xpl_parser.y"
	{ yyval.node = new xpl::function_def_node(LINE, true, yystack.l_mark[-5].type, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].node); 	}
break;
case 23:
#line 104 "xpl_parser.y"
	{ yyval.node = new xpl::function_def_node(LINE, false, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].node); }
break;
case 24:
#line 105 "xpl_parser.y"
	{ yyval.node = new xpl::function_def_node(LINE, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].node); }
break;
case 25:
#line 108 "xpl_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence;		}
break;
case 26:
#line 109 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE);	}
break;
case 27:
#line 112 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node);		}
break;
case 28:
#line 113 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-2].sequence);	}
break;
case 29:
#line 116 "xpl_parser.y"
	{ yyval.node = new xpl::variable_decl_node(LINE, yystack.l_mark[-1].type, yystack.l_mark[0].s, NULL, true, false, true); }
break;
case 30:
#line 119 "xpl_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_INT); 	}
break;
case 31:
#line 120 "xpl_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_STRING); 	}
break;
case 32:
#line 121 "xpl_parser.y"
	{ yyval.type = new basic_type(8, basic_type::TYPE_DOUBLE); 	}
break;
case 33:
#line 122 "xpl_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[-1].type; }
break;
case 34:
#line 125 "xpl_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 35:
#line 126 "xpl_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].d); 	}
break;
case 36:
#line 127 "xpl_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s);	}
break;
case 37:
#line 128 "xpl_parser.y"
	{ yyval.expression = new xpl::null_node(LINE); }
break;
case 38:
#line 131 "xpl_parser.y"
	{ yyval.s = yystack.l_mark[0].s;	}
break;
case 39:
#line 132 "xpl_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s + *yystack.l_mark[0].s); delete yystack.l_mark[-1].s; delete yystack.l_mark[0].s;	}
break;
case 40:
#line 135 "xpl_parser.y"
	{ yyval.node = new xpl::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); 		}
break;
case 41:
#line 136 "xpl_parser.y"
	{ yyval.node = new xpl::block_node(LINE, yystack.l_mark[-1].sequence, new cdk::sequence_node(LINE)); 	}
break;
case 42:
#line 137 "xpl_parser.y"
	{ yyval.node = new xpl::block_node(LINE, new cdk::sequence_node(LINE), yystack.l_mark[-1].sequence); 	}
break;
case 43:
#line 138 "xpl_parser.y"
	{ yyval.node = new xpl::block_node(LINE, new cdk::sequence_node(LINE), new cdk::sequence_node(LINE)); 	}
break;
case 44:
#line 141 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); 		}
break;
case 45:
#line 142 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); 	}
break;
case 46:
#line 145 "xpl_parser.y"
	{ yyval.node = new xpl::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 47:
#line 146 "xpl_parser.y"
	{ yyval.node = new xpl::print_node(LINE, yystack.l_mark[-1].expression); }
break;
case 48:
#line 147 "xpl_parser.y"
	{ yyval.node = new xpl::println_node(LINE, yystack.l_mark[-1].expression);	}
break;
case 49:
#line 148 "xpl_parser.y"
	{ yyval.node = new xpl::while_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 50:
#line 149 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 51:
#line 150 "xpl_parser.y"
	{ yyval.node = new xpl::next_node(LINE); }
break;
case 52:
#line 151 "xpl_parser.y"
	{ yyval.node = new xpl::stop_node(LINE); }
break;
case 53:
#line 152 "xpl_parser.y"
	{ yyval.node = new xpl::return_node(LINE); }
break;
case 54:
#line 153 "xpl_parser.y"
	{ yyval.node = new xpl::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 55:
#line 154 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].node, yystack.l_mark[0].node); }
break;
case 56:
#line 155 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 57:
#line 159 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_plus_node(LINE, yystack.l_mark[-6].lvalue, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, new cdk::integer_node(LINE, 1), yystack.l_mark[0].node);	 }
break;
case 58:
#line 160 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_minus_node(LINE, yystack.l_mark[-6].lvalue, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, new cdk::integer_node(LINE, 1), yystack.l_mark[0].node);	 }
break;
case 59:
#line 161 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_plus_node(LINE, yystack.l_mark[-8].lvalue, yystack.l_mark[-6].expression, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].node);	 	}
break;
case 60:
#line 162 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_minus_node(LINE, yystack.l_mark[-8].lvalue, yystack.l_mark[-6].expression, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].node);	}
break;
case 61:
#line 165 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 62:
#line 166 "xpl_parser.y"
	{ yyval.node = new xpl::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 63:
#line 167 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].node, yystack.l_mark[0].node); }
break;
case 64:
#line 171 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 65:
#line 172 "xpl_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 66:
#line 173 "xpl_parser.y"
	{ yyval.expression = new xpl::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 67:
#line 174 "xpl_parser.y"
	{ yyval.expression = new cdk::not_node(LINE, yystack.l_mark[0].expression);}
break;
case 68:
#line 175 "xpl_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 69:
#line 176 "xpl_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 70:
#line 177 "xpl_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 71:
#line 178 "xpl_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 72:
#line 179 "xpl_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 73:
#line 180 "xpl_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 74:
#line 181 "xpl_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 75:
#line 182 "xpl_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 76:
#line 183 "xpl_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 77:
#line 184 "xpl_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 78:
#line 185 "xpl_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 79:
#line 186 "xpl_parser.y"
	{ yyval.expression = new cdk::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 80:
#line 187 "xpl_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 81:
#line 188 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 82:
#line 189 "xpl_parser.y"
	{ yyval.expression = new xpl::mem_alloc_node(LINE, yystack.l_mark[-1].expression); }
break;
case 83:
#line 190 "xpl_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 84:
#line 191 "xpl_parser.y"
	{ yyval.expression = new cdk::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 85:
#line 192 "xpl_parser.y"
	{ yyval.expression = new xpl::mem_address_node(LINE, yystack.l_mark[-1].lvalue);}
break;
case 86:
#line 193 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 87:
#line 194 "xpl_parser.y"
	{ yyval.expression = new xpl::read_node(LINE);}
break;
case 88:
#line 197 "xpl_parser.y"
	{ yyval.expression = new xpl::function_call_node(LINE, yystack.l_mark[-2].s, NULL); }
break;
case 89:
#line 198 "xpl_parser.y"
	{ yyval.expression = new xpl::function_call_node(LINE, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); 	}
break;
case 90:
#line 201 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression);		}
break;
case 91:
#line 202 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence);	}
break;
case 92:
#line 204 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 93:
#line 207 "xpl_parser.y"
	{ yyval.lvalue = new cdk::identifier_node(LINE, yystack.l_mark[0].s); }
break;
case 94:
#line 208 "xpl_parser.y"
	{ yyval.lvalue = new xpl::indexing_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression);}
break;
#line 1296 "xpl_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
