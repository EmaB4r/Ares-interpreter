//
// Created by emanuele on 17/05/24.
//

#include "Arestd.h"
#include <stdio.h>
#include <ctype.h>

void ares_print(scope_t* scope,  ast_node_t *function_tree){
    ast_node_t* arg = function_tree->right;
    while(arg!=NULL){
        switch (arg->token->type) {
            case TOKEN_STRING : printf("str: %s", arg->token->value); break;
            case TOKEN_NUMBER : printf("num: %d", strtol(arg->token->value, NULL, 10)); break;
            case TOKEN_ID :{
                token_t * value_token=scope_get_variable_value(scope, arg->token);
                switch (value_token->type) {
                    case TOKEN_STRING: printf("var_str: %s", value_token->value); break;
                    case TOKEN_NUMBER: printf("var_num: %d", value_token->num); break;
                } break;
            }
        }
        arg=arg->right;
    }
}

void ares_println(scope_t* scope,  ast_node_t *function_tree){
    ast_node_t* arg = function_tree->right;
    while(arg!=NULL){
        switch (arg->token->type) {
            case TOKEN_STRING : printf("str: %s", arg->token->value); break;
            case TOKEN_NUMBER : printf("num: %d", strtol(arg->token->value, NULL, 10)); break;
            case TOKEN_ID :{
                token_t * value_token=scope_get_variable_value(scope, arg->token);
                switch (value_token->type) {
                    case TOKEN_STRING: printf("var_str: %s", value_token->value); break;
                    case TOKEN_NUMBER: printf("var_num: %d", value_token->num); break;
                } break;
            }
        }
        arg=arg->right;
    }
    printf("\n");
}