//
// Created by emanuele on 16/05/24.
//

#ifndef PARSER_AST_H
#define PARSER_AST_H
#include <stdlib.h>
#include "token.h"
enum ast_e{
    AST_VARIABLE,
    AST_VARIABLE_DEFINITION,
    AST_DIGIT,
    AST_STRING,
    AST_FUNCTION_CALL,
    AST_FUNCTION_CALL_ARG,
    AST_FACTOR, //FACTOR --> DIGIT OR (EXPR) --> TERMINALE
    AST_EXPRESSION,  //EXPR --> EXPR+TERM | EXPR-TERM | TERM
    AST_TERM, // TERM --> TERM*FACTOR | TERM/FACTOR | FACTOR
    AST_NOOP
};

typedef struct ast_node_struct{
    enum ast_e type;
    int num_children;
    token_t * token;
    struct ast_node_struct* left;
    struct ast_node_struct* right;



}ast_node_t;


ast_node_t * ast_new_node(int type, token_t * token);

void ast_node_add_child(ast_node_t * parent, ast_node_t * child);

void ast_print_rec(ast_node_t * root);

int ast_eval(ast_node_t * root);

#endif //PARSER_AST_H
