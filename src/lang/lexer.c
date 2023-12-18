#include "lexer.h" 

char* Lexer_TokenType_getTypeName(
    int ttype
) {
    char* name = NULL;
    
    switch (ttype) {
        case TT_INT: name = "INT"; break;
        case TT_STRING: name = "STRING"; break;
        case TT_ID: name = "ID"; break;
        case TT_COMMA: name = "COMMA"; break;
        case TT_ELIPSIS: name = "ELIPSIS"; break;
        case TT_ASSIGN: name = "ASSIGN"; break;
        case TT_EQ: name = "EQ"; break;
        case TT_NEQ: name = "NEQ"; break;
        case TT_LT: name = "LT"; break;
        case TT_GT: name = "GT"; break;
        case TT_LTE: name = "LTE"; break;
        case TT_GTE: name = "GTE"; break;
        case TT_NOT: name = "NOT"; break;
        case TT_ADD: name = "ADD"; break;
        case TT_SUB: name = "SUB"; break;
        case TT_MUL: name = "MUL"; break;
        case TT_DIV: name = "DIV"; break;
        case TT_L_NS: name = "LOCAL_NAMESPACE"; break;
        case TT_G_NS: name = "GLOBAL_NAMESPACE"; break;
        case TT_BRACKETL: name = "BRACKETL"; break;
        case TT_BRACKETR: name = "BRACKETR"; break;
        case TT_SQRBRACKETL: name = "SQRBRACKETL"; break;
        case TT_SQRBRACKETR: name = "SQRBRACKETR"; break;
        case TT_CRLBRACKETL: name = "CRLBRACKETL"; break;
        case TT_CRLBRACKETR: name = "CRLBRACKETR"; break;
        case TT_CONTINUE: name = "CONTINUE"; break;
        case TT_BREAK: name = "BREAK"; break;
        case TT_RETURN: name = "RETURN"; break;
        case TT_LET: name = "LET"; break;
        case TT_IF: name = "IF"; break;
        case TT_ELSEIF: name = "ELSEIF"; break;
        case TT_ELSE: name = "ELSE"; break;
        case TT_FUNCTION: name = "FUNCTION"; break;
        case TT_FOR: name = "FOR"; break;
        case TT_WHILE: name = "WHILE"; break;
        case TT_MATCH: name = "MATCH"; break;
        case TT_ENDIF: name = "ENDIF"; break;
        case TT_ENDFUNCTION: name = "ENDFUNCTION"; break;
        case TT_ENDFOR: name = "ENDFOR"; break;
        case TT_ENDWHILE: name = "ENDWHILE"; break;
        case TT_ENDMATCH: name = "ENDMATCH"; break;
        case TT_COUNT:
        default: 
            name = "UNKNOWN"; break;
    }

    return name;
}

Lexer_Token* Lexer_run(
    char* code, 
    size_t size
) {
    Lexer_Token* tokens = NULL;
    size_t line = 1;
    size_t col = 1;
    size_t i = 0;
    size_t bi = 0;
    char buffer[100] = { 0 };

    while (i < size) {
        int ttype = TT_NONE;
        Lexer_Span span = (Lexer_Span) {
            .begin = col,
            .end = 0
        };

        /* remove comments */
        if (code[i] == '#') {
            while (code[i] != '\n') { col++; i++; }
            continue;
        }

        /* skip whitespace */
        if (code[i] == ' ')  { col++; i++; continue; }
        if (code[i] == '\t') { col += 4; i++; continue; }
        if (code[i] == '\n') { col = 1; i++; line++; continue; }

        /* check for id */
        if ((code[i] >= 'a' && code[i] <= 'z') || code[i] == '_') {
            while ((code[i] >= 'a' && code[i] <= 'z') || code[i] == '_') {
                buffer[bi++] = code[i++];
                col++;
            }

            ttype = TT_ID;

            /* check if id is actually a reserved keyword */
            if (rsh_strcmp("let", buffer, 3) == RSH_STRCMP_EQ) {
                if (bi != 3) goto id_end;
                ttype = TT_LET;
            } else if (rsh_strcmp("if", buffer, 2) == RSH_STRCMP_EQ) {
                if (bi != 2) goto id_end;
                ttype = TT_IF;
            } else if (rsh_strcmp("elseif", buffer, 6) == RSH_STRCMP_EQ) {
                if (bi != 6) goto id_end;
                ttype = TT_ELSEIF;
            } else if (rsh_strcmp("else", buffer, 4) == RSH_STRCMP_EQ) {
                if (bi != 4) goto id_end;
                ttype = TT_ELSE;
            } else if (rsh_strcmp("function", buffer, 8) == RSH_STRCMP_EQ) {
                if (bi != 8) goto id_end;
                ttype = TT_FUNCTION;
            } else if (rsh_strcmp("while", buffer, 5) == RSH_STRCMP_EQ) {
                if (bi != 5) goto id_end;
                ttype = TT_WHILE;
            } else if (rsh_strcmp("for", buffer, 3) == RSH_STRCMP_EQ) {
                if (bi != 3) goto id_end;
                ttype = TT_FOR;
            } else if (rsh_strcmp("match", buffer, 5) == RSH_STRCMP_EQ) {
                if (bi != 5) goto id_end;
                ttype = TT_MATCH;
            } else if (rsh_strcmp("endif", buffer, 5) == RSH_STRCMP_EQ) {
                if (bi != 5) goto id_end;
                ttype = TT_ENDIF;
            } else if (rsh_strcmp("endfunction", buffer, 11) == RSH_STRCMP_EQ) {
                if (bi != 11) goto id_end;
                ttype = TT_ENDFUNCTION;
            } else if (rsh_strcmp("endwhile", buffer, 8) == RSH_STRCMP_EQ) {
                if (bi != 8) goto id_end;
                ttype = TT_ENDWHILE;
            } else if (rsh_strcmp("endfor", buffer, 6) == RSH_STRCMP_EQ) {
                if (bi != 6) goto id_end;
                ttype = TT_ENDFOR;
            } else if (rsh_strcmp("endmatch", buffer, 8) == RSH_STRCMP_EQ) {
                if (bi != 8) goto id_end;
                ttype = TT_ENDMATCH;
            } else if (rsh_strcmp("continue", buffer, 8) == RSH_STRCMP_EQ) {
                if (bi != 8) goto id_end;
                ttype = TT_CONTINUE;
            } else if (rsh_strcmp("break", buffer, 5) == RSH_STRCMP_EQ) {
                if (bi != 5) goto id_end;
                ttype = TT_BREAK;
            } else if (rsh_strcmp("return", buffer, 6) == RSH_STRCMP_EQ) {
                if (bi != 6) goto id_end;
                ttype = TT_RETURN;
            }

id_end:
            span.end = col;
        }

        /* check for int */ 
        else if (code[i] >= '0' && code[i] <= '9') {
            while (code[i] >= '0' && code[i] <= '9') {
                buffer[bi++] = code[i++];
                col++;
            }

            span.end = col;
            ttype = TT_INT;
        }

        /* check for string */
        else if (code[i] == '"' || code[i] == '\'') {
            char delim = code[i];
            i++; col++;
            while (code[i] != delim) {
                buffer[bi++] = code[i++];
                col++;
            }
            i++; col++;

            span.end = col;
            ttype = TT_STRING; 
        }

        /* operators/brackets/sugar */
        else {
            switch (code[i]) {
                case '(': ttype = TT_BRACKETL; i++; col++; break;
                case ')': ttype = TT_BRACKETR; i++; col++; break;
                case '[': ttype = TT_SQRBRACKETL; i++; col++; break;
                case ']': ttype = TT_SQRBRACKETR; i++; col++; break;
                case '{': ttype = TT_CRLBRACKETL; i++; col++; break;
                case '}': ttype = TT_CRLBRACKETR; i++; col++; break;
                case '=': {
                            if (code[i + 1] == '=') {
                                ttype = TT_EQ;
                                i += 2; col += 2; 
                            } else {
                                ttype = TT_ASSIGN;
                                i++; col++; 
                            }
                          } break;
                case '!': {
                            if (code[i + 1] == '=') {
                                ttype = TT_NEQ;
                                i += 2; col += 2; 
                            } else {
                                ttype = TT_NOT;
                                i++; col++; 
                            }
                          } break;
                case '<': {
                            if (code[i + 1] == '=') {
                                ttype = TT_LTE;
                                i += 2; col += 2; 
                            } else {
                                ttype = TT_LT;
                                i++; col++; 
                            }
                          } break;
                case '>':{
                            if (code[i + 1] == '=') {
                                ttype = TT_GTE;
                                i += 2; col += 2; 
                            } else {
                                ttype = TT_GT;
                                i++; col++; 
                            }
                          } break; 
                case '+': ttype = TT_ADD; i++; col++; break;
                case '-': ttype = TT_SUB; i++; col++; break;
                case '/': ttype = TT_DIV; i++; col++; break;
                case '*': ttype = TT_MUL; i++; col++; break;
                case ':': ttype = TT_L_NS; i++; col++; break;
                case ',': ttype = TT_COMMA; i++; col++; break;
                case ';': ttype = TT_SEMICOLON; i++; col++; break;
                case '|': ttype = TT_PIPE; i++; col++; break;
                case '\\': ttype = TT_G_NS; i++; col++; break;
                case '.': {
                            if (code[i + 1] == '.' && code[i + 2] == '.') {
                                ttype = TT_ELIPSIS;
                                i += 3; col += 3;
                            } else {
                                ttype = TT_NONE;
                                i++; col++;
                                /* TODO: build an error here */ 
                            }
                          } break;
            }
            span.end = col;
        }

        /* build the token */
        Lexer_Token* ptr = tokens;
        if (ptr == NULL) {
            tokens = malloc(sizeof(Lexer_Token));
            if (!tokens) {
                /* TODO: build an error here */
                return NULL;
            }

            rsh_strcpy(tokens->value, buffer, bi);
            tokens->ttype = ttype;
            tokens->colSpan = span;
            tokens->line = line;
            tokens->next = NULL;
        } else {
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }

            ptr->next = malloc(sizeof(Lexer_Token));
            rsh_strcpy(ptr->next->value, buffer, bi);
            ptr->next->ttype = ttype;
            ptr->next->colSpan = span;
            ptr->next->line = line;
            ptr->next->next = NULL;
        }

        /* reset buffer */
        bi = 0;
        rsh_strset(buffer, 100, '\0');
    }

    return tokens;
}
