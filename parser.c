//
// Created by emanuele on 16/05/24.
//

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

parser_t * parser_init(lexer_t * lexer){
    parser_t * p = malloc(sizeof (*p));
    p->lexer=lexer;
    p->abstract_syntax_trees_vector= NULL;
    p->ast_total_num=0;
    p->previous_token=NULL;
    p->current_token= lexer_get_next_token(lexer);
    return p;
}

void parser_eat(parser_t * parser){
    parser->previous_token=parser->current_token;
    parser->current_token= lexer_get_next_token(parser->lexer);
}

void parser_digest(parser_t * parser, int expected_token_type){
    if(parser->current_token->type==expected_token_type){
        parser_eat(parser);
    }
    else{
        if(expected_token_type==TOKEN_SEMI)
            printf("missing ';' after '%s'\n", parser->previous_token->value);
        else
            printf("unexpected token '%s' of type '%s', expected '%s'\n",
               parser->current_token->value, print_table[parser->current_token->type],
               print_table[expected_token_type]
               );
        exit(1);
    }
}


ast_node_t * parser_parse_expression(parser_t * parser){
    switch (parser->current_token->type) {
        case TOKEN_ID:return parser_parse_id(parser); break;
        case TOKEN_STRING: return parser_parse_string(parser);break;
    }
    ast_node_t * f1 = parser_parse_term(parser);
    while(parser->current_token->type==TOKEN_PLUS_SIGN || parser->current_token->type==TOKEN_MINUS_SIGN){
        ast_node_t *sign = ast_new_node(AST_EXPRESSION, parser->current_token);
        parser_eat(parser);
        ast_node_add_child(sign, f1);
        ast_node_add_child(sign, parser_parse_term(parser));
        f1=sign;
    }
    return f1;
}
ast_node_t * parser_parse_term(parser_t * parser){
    ast_node_t * f1 = parser_parse_factor(parser);
    while(parser->current_token->type==TOKEN_MULTIPLY_SIGN || parser->current_token->type==TOKEN_DIVIDE_SIGN){
        ast_node_t *sign = ast_new_node(AST_EXPRESSION, parser->current_token);
        parser_eat(parser);
        ast_node_add_child(sign, f1);
        ast_node_add_child(sign, parser_parse_factor(parser));
        f1=sign;
    }
    return f1;
}
ast_node_t * parser_parse_factor(parser_t * parser){
    if(parser->current_token->type==TOKEN_LPAREN){
        parser_eat(parser);
        ast_node_t * expr = parser_parse_expression(parser);
        parser_eat(parser);
        return expr;
    }
    parser->current_token->num= atoi(parser->current_token->value);
    ast_node_t * node = ast_new_node(AST_DIGIT, parser->current_token);
    parser_eat(parser);
    return node;
}


void parser_append_ast(parser_t * parser, ast_node_t * ast){
    if(parser->ast_total_num) {
        parser->ast_total_num++;
        parser->abstract_syntax_trees_vector = realloc(parser->abstract_syntax_trees_vector, sizeof (ast_node_t*)*parser->ast_total_num);
    }
    else{
        parser->ast_total_num++;
        parser->abstract_syntax_trees_vector = malloc(sizeof (ast_node_t*));
    }
    parser->abstract_syntax_trees_vector[parser->ast_total_num-1]=ast;

}


ast_node_t * parser_parse_statement(parser_t * parser){
    switch (parser->current_token->type) {
        case TOKEN_LPAREN: return parser_parse_expression(parser); break;
        case TOKEN_END_LEXING: return ast_new_node(AST_NOOP, NULL); break;
        case TOKEN_ID: return parser_parse_id(parser); break;
    }
}


void parser_parse_statements(parser_t * parser){

    do{
        parser_append_ast(parser, parser_parse_statement(parser));
        parser_digest(parser, TOKEN_SEMI);
    }while(parser->current_token->type!=TOKEN_END_LEXING);
}


void parser_parse(parser_t * parser){
    parser_parse_statements(parser);
}

ast_node_t * parser_parse_variable_definition(parser_t * parser){
    parser_digest(parser, TOKEN_ID); // digest var keyword
    ast_node_t * variable_name= ast_new_node(AST_VARIABLE_DEFINITION, parser->current_token);
    parser_digest(parser, TOKEN_ID); // digest <var_name> keyword
    parser_digest(parser, TOKEN_EQUALS); // digest = keyword
    ast_node_t * variable_value= parser_parse_expression(parser);
    variable_name->right=variable_value;
}

ast_node_t * parser_parse_variable(parser_t * parser){
    ast_node_t * variable_name= ast_new_node(AST_VARIABLE, parser->current_token);
    parser_digest(parser, TOKEN_ID); // digest <var_name> keyword
    if(parser->current_token->type==TOKEN_LPAREN){
        return parser_parse_function_call(parser);
    }
    if(parser->current_token->type==TOKEN_EQUALS){
        parser_digest(parser, TOKEN_EQUALS);
        variable_name->right= parser_parse_expression(parser);
    }
    return variable_name;
}

ast_node_t * parser_parse_id(parser_t * parser){
    if(!strcmp(parser->current_token->value,"var")){
        return parser_parse_variable_definition(parser);
    }
    return parser_parse_variable(parser);
}

void insert_right_function_call_args(ast_node_t* function_par, ast_node_t* arg){
    if(function_par->right!=NULL)
        insert_right_function_call_args(function_par->right, arg);
    else
        function_par->right=arg;
}


ast_node_t * parser_parse_function_call(parser_t * parser){
    ast_node_t * function_call= ast_new_node(AST_FUNCTION_CALL, parser->previous_token);
    while(parser->current_token->type!=TOKEN_RPAREN){
        parser_eat(parser); // eat '(' or ',' if not first iteration
        if(parser->current_token->type!=TOKEN_RPAREN){
            ast_node_t * argument = parser_parse_expression(parser);
            insert_right_function_call_args(function_call, argument);
        }
    }
    parser_digest(parser, TOKEN_RPAREN);
    return function_call;
}

ast_node_t * parser_parse_string(parser_t * parser){
    ast_node_t * string = ast_new_node(AST_STRING, parser->current_token);
    parser_digest(parser, TOKEN_STRING);
    return string;
}