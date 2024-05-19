#include "token.h" 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
token_t * token_init(char * str, int type){
    token_t * t =malloc(sizeof(token_t));
    t->value=str;
    t->type=type;
    return t;
}

void token_print(token_t* token){
    printf("token value: %s, token type: %s", token->value, print_table[token->type]);
}