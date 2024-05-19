#include "lexer.h"
#include <stdlib.h>
#include "token.h"
#include <ctype.h>



lexer_t * lexer_init(char* source_code){
    lexer_t * l=malloc(sizeof(lexer_t));
    l->source_code=source_code;
    l->text_index=0;
    l->current_char=l->source_code[l->text_index];
    return l;
}

void lexer_advance(lexer_t * lexer){
    lexer->text_index++;
    lexer->current_char=lexer->source_code[lexer->text_index];
}


void lexer_skip_whitespaces(lexer_t * lexer){
    while (lexer->current_char==' ' || lexer->current_char=='\n')
        lexer_advance(lexer);
}

char* lexer_collect_string(lexer_t* lexer){
    int i=0;
    char * str=malloc(2*sizeof(char));
    lexer_advance(lexer);
    while(lexer->current_char!='"'){
        str[i]=lexer->current_char;
        i++;
        str[i]='\0';
        lexer_advance(lexer);
        str = realloc(str, sizeof(str)/sizeof(char)+1);
    }
    lexer_advance(lexer);
    return str;
}

char* lexer_collect_number(lexer_t* lexer){
    int i=0;
    char * str=malloc(2*sizeof(char));
    while(isdigit(lexer->current_char)||lexer->current_char=='.'){
        str[i]=lexer->current_char;
        i++;
        str[i]='\0';
        lexer_advance(lexer);
        str = realloc(str, sizeof(str)/sizeof(char)+1);
    }
    return str;
}

char* lexer_collect_id(lexer_t* lexer){
    int i=0;
    char * str=malloc(2*sizeof(char));
    while(isalnum(lexer->current_char)){
        str[i]=lexer->current_char;
        i++;
        str[i]='\0';
        lexer_advance(lexer);
        str = realloc(str, sizeof(str)/sizeof(char)+1);
    }
    return str;
}

char* lexer_get_char_as_string(lexer_t* lexer){
    char* c=malloc(sizeof(char)*2);
    c[0]=lexer->current_char;
    c[1]='\0';
    lexer_advance(lexer);
    return c;
}


token_t * lexer_get_next_token(lexer_t * lexer){
    lexer_skip_whitespaces(lexer);
    if(isdigit(lexer->current_char)) return token_init(lexer_collect_number(lexer), TOKEN_NUMBER);

    switch (lexer->current_char)
    {
    case '"': return token_init(lexer_collect_string(lexer), TOKEN_STRING); break;
    case '=': return token_init(lexer_get_char_as_string(lexer), TOKEN_EQUALS); break;
    case ':': return token_init(lexer_get_char_as_string(lexer), TOKEN_COLON); break;
    case ',': return token_init(lexer_get_char_as_string(lexer), TOKEN_COMMA); break;
    case ';': return token_init(lexer_get_char_as_string(lexer), TOKEN_SEMI); break;
    case '(': return token_init(lexer_get_char_as_string(lexer), TOKEN_LPAREN); break;
    case ')': return token_init(lexer_get_char_as_string(lexer), TOKEN_RPAREN); break;
    case '{': return token_init(lexer_get_char_as_string(lexer), TOKEN_LBRACKET); break;
    case '}': return token_init(lexer_get_char_as_string(lexer), TOKEN_RBRACKET); break;
    case '+': return token_init(lexer_get_char_as_string(lexer), TOKEN_PLUS_SIGN); break;
    case '-': return token_init(lexer_get_char_as_string(lexer), TOKEN_MINUS_SIGN); break;
    case '*': return token_init(lexer_get_char_as_string(lexer), TOKEN_MULTIPLY_SIGN); break;
    case '/': return token_init(lexer_get_char_as_string(lexer), TOKEN_DIVIDE_SIGN); break;
    case '\0': return token_init("NULL", TOKEN_END_LEXING); break;
    default: return token_init(lexer_collect_id(lexer), TOKEN_ID); break;
    }
}
