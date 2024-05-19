//
// Created by emanuele on 17/05/24.
//

#include "visitor.h"
#include <string.h>
#include <stdio.h>
#include "Arestd.h"
#include "math.h"


void visitor_visit_parser(parser_t * parser){
    scope_t * scope = scope_init();
    for (int i=0; i<parser->ast_total_num; i++){
        visitor_visit(scope, parser->abstract_syntax_trees_vector[i]);
    }
}

void visitor_visit(scope_t * scope, ast_node_t* node){
    switch (node->type) {
        case AST_VARIABLE_DEFINITION: visitor_visit_variable_definition(scope, node); break;
        case AST_VARIABLE: visitor_visit_variable(scope, node); break;
        case AST_FUNCTION_CALL: visitor_visit_function_call(scope, node); break;
        case AST_NOOP: return; break;
    }
}

void visitor_visit_variable_definition(scope_t * scope, ast_node_t* node){
    token_t * variable_val =node->right->token;
    if(node->right->type==AST_EXPRESSION){
        token_t * eval_expr= token_init(NULL, TOKEN_NUMBER);
        eval_expr->num= ast_eval(node->right);
        scope_add_variable(scope, node->token, eval_expr);
    }
    scope_add_variable(scope, node->token, variable_val);
}

void visitor_visit_function_definition(scope_t * scope, ast_node_t* node);

void visitor_visit_variable(scope_t * scope, ast_node_t* node){
    scope_update_variable(scope, node->token, node->right->token);
}

void visitor_visit_function_call(scope_t * scope, ast_node_t* node){
    if(!strcmp(node->token->value, "print")){
        ares_print(scope, node);
    }
    if(!strcmp(node->token->value, "println")){
        ares_println(scope, node);
    }
}

void visitor_visit_string(scope_t * scope, ast_node_t* node);

void visitor_visit_compound(scope_t * scope, ast_node_t* node);
