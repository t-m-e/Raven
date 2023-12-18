#include "stdio.h"

#include "lexer.h"

int main(
    int argc,
    char** argv
) {
    if (argc == 1) {
        printf("[error] no input file specified\n");
        return -1;
    }

    FILE* file = fopen(argv[1], "r");
    char* buffer = NULL;
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = calloc(1, size + 1);
    fread(buffer, 1, size, file);

    Lexer_Token* tokens = Lexer_run(buffer, size);

    /* print out the tokens */
    Lexer_Token* ptr = tokens;
    while (ptr != NULL) {
        printf("[token %lu:%lu-%lu] value: %s, type: %s\n",
            ptr->line, 
            ptr->colSpan.begin,
            ptr->colSpan.end,
            ptr->value, 
            Lexer_TokenType_getTypeName(ptr->ttype));
        ptr = ptr->next;
    }

    return 0;
}

