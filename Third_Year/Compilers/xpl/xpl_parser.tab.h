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
extern YYSTYPE yylval;
