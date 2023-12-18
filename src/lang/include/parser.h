#ifndef RAVENSH_LANG_PARSER
#define RAVENSH_LANG_PARSER

#include "lexer.h"
#include "debug.h"

typedef struct astLet_t     Parser_AstLet;
typedef struct astFun_t     Parser_AstFun;
typedef struct astFunArgs_t Parser_AstFunArgs;
typedef struct astIf_t      Parser_AstIf;
typedef struct astElseIf_t  Parser_AstElseIf;
typedef struct astElse_t    Parser_AstElse;
typedef struct astMatch_t   Parser_AstMatch;
typedef struct astMatchCond_t Parser_AstMatchCond;
typedef struct astFor_t     Parser_AstFor;
typedef struct astWhile_t   Parser_AstWhile;
typedef struct astBreak_t   Parser_AstBreak;
typedef struct astContinue_t Parser_AstContinue;
typedef struct astBinop_t   Parser_AstBinop;
typedef struct astMonop_t   Parser_AstMonop;
typedef union  ast_t        Parser_Ast;

typedef struct astLet_t {
    Lexer_Token* ns;
    Lexer_Token* name;
    Parser_Ast* expr;
} Parser_AstLet;

typedef struct astFunArgs_t {
    Lexer_Token* ns;
    Lexer_Token* name;
    int isVariadic; /* 0 == false, else true */
} Parser_AstFunArgs;

typedef struct astFun_t {
    Lexer_Token* ns;
    Lexer_Token* name;

} Parser_AstFun;

#endif 
