//
// Created by emanuele on 16/05/24.
//

#include "AST.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ast_node_t * ast_new_node(int type, token_t * token){
    ast_node_t * node = malloc(sizeof (ast_node_t ));
    node->type=type;
    node->token=token;
    node->left=NULL;
    node->right=NULL;
    node->num_children=0;
    return node;
}

void ast_node_add_child(ast_node_t * parent, ast_node_t * child){
    if(parent->num_children){
        parent->right=child;
    }
    else{
        parent->left=child;
    }
    parent->num_children++;
}

void ast_print_rec(ast_node_t * root){
    if(root!=NULL){
        printf("(");
        ast_print_rec(root->left);
        printf("  ");
        token_print(root->token);
        printf("  ");
        ast_print_rec(root->left);
        printf(")");
    }
}

int ast_eval(ast_node_t * root){
    if(root->type==AST_DIGIT)
        return strtol(root->token->value, NULL, 10);
    if (!strcmp("+", root->token->value)) {
        return ast_eval(root->left) + ast_eval(root->right);
    }
    if (!strcmp("-", root->token->value)) {
        return ast_eval(root->left) - ast_eval(root->right);
    }
    if (!strcmp("*", root->token->value)) {
        return ast_eval(root->left) * ast_eval(root->right);
    }
    if (!strcmp("/", root->token->value)) {
        return ast_eval(root->left) / ast_eval(root->right);
    }
}