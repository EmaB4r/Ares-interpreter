#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct lexer_struct
{
    char* source_code;
    char current_char;
    int text_index;
}lexer_t;

lexer_t * lexer_init(char* source_code);

token_t * lexer_get_next_token(lexer_t * lexer);

void lexer_advance(lexer_t * lexer);

void lexer_skip_whitespaces(lexer_t * lexer);

char* lexer_collect_string(lexer_t* lexer);

char* lexer_collect_number(lexer_t* lexer);

char* lexer_get_char_as_string(lexer_t* lexer);



#endif