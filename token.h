#ifndef TOKEN_H
#define TOKEN_H


static char * print_table[]={
    "TOKEN_ID",
    "TOKEN_STRING",
    "TOKEN_NUMBER",
    "TOKEN_EQUALS",
    "TOKEN_COLON",
    "TOKEN_COMMA",
    "TOKEN_SEMI",
    "TOKEN_LPAREN",
    "TOKEN_RPAREN",
    "TOKEN_LBRACKET",
    "TOKEN_RBRACKET",
    "TOKEN_PLUS_SIGN",
    "TOKEN_MINUS_SIGN",
    "TOKEN_MULTIPLY_SIGN",
    "TOKEN_DIVIDE_SIGN",
    "TOKEN_END_LEXING"
};


enum token_type{
        TOKEN_ID,

        TOKEN_STRING,
        TOKEN_NUMBER,

        TOKEN_EQUALS,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_SEMI,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACKET,
        TOKEN_RBRACKET,

        TOKEN_PLUS_SIGN,
        TOKEN_MINUS_SIGN,
        TOKEN_MULTIPLY_SIGN,
        TOKEN_DIVIDE_SIGN,

        TOKEN_END_LEXING
};




typedef struct token_struct
{
    enum token_type type;
    int num;
    char* value;

}token_t;

token_t * token_init(char * str, int type);

void token_print(token_t* token);

#endif