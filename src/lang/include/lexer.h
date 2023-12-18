#ifndef RAVENSH_LANG_LEXER
#define RAVENSH_LANG_LEXER

#include <stdlib.h>

#include "rsh_string.h"

/* 
 * token column span
 */
typedef struct span_t {
    size_t begin;
    size_t end;
} Lexer_Span;

/* 
 * token enum types
 */
enum {
    /* data types */
    TT_NONE,
    TT_INT,
    TT_STRING,
    TT_ID,
    
    /* operators and sugar syntax */
    TT_PIPE,
    TT_SEMICOLON,   /* ; */
    TT_COMMA,       /* , */
    TT_ELIPSIS,     /* ... */
    TT_ASSIGN,      /* = */
    TT_EQ,
    TT_NEQ,
    TT_LT,
    TT_GT,
    TT_LTE,
    TT_GTE,
    TT_NOT,         /* ! */
    TT_ADD,         /* + */
    TT_SUB,         /* - */
    TT_MUL,         /* * */
    TT_DIV,         /* / */
    TT_L_NS,        /* local name space ':' */
    TT_G_NS,        /* global name space '\' */
    
    /* bracket types */
    TT_BRACKETL,
    TT_BRACKETR,
    TT_SQRBRACKETL,
    TT_SQRBRACKETR,
    TT_CRLBRACKETL,
    TT_CRLBRACKETR,

    /* exchange token buffer for solidified token types */
    TT_CONTINUE,
    TT_BREAK,
    TT_RETURN,

    TT_LET,
    TT_IF,
    TT_ELSEIF,
    TT_ELSE,
    TT_FUNCTION,
    TT_FOR,
    TT_WHILE,
    TT_MATCH,

    TT_ENDIF,
    TT_ENDFUNCTION,
    TT_ENDFOR,
    TT_ENDWHILE,
    TT_ENDMATCH,

    /* count of token types */
    TT_COUNT
};

char* Lexer_TokenType_getTypeName(
    int ttype
);

/*
 * linked token list
 */
typedef struct token_t {
    char value[100];
    int ttype;
    Lexer_Span  colSpan;
    size_t line;
    struct token_t* next;
} Lexer_Token;

/*
 * lexer function
 * @return Token*
 */
Lexer_Token* Lexer_run(
    char* code,
    size_t size
);

#endif
