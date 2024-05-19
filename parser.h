//
// Created by emanuele on 16/05/24.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H
#include "lexer.h"
#include "AST.h"


typedef struct parser_struct{
    lexer_t * lexer;
    long ast_total_num;
    ast_node_t ** abstract_syntax_trees_vector;
    token_t* current_token;
    token_t* previous_token;
}parser_t;


parser_t * parser_init(lexer_t * lexer);

void parser_eat(parser_t * parser);
void parser_digest(parser_t * parser, int expected_token_type);

void parser_parse(parser_t * parser);
void parser_parse_statements(parser_t * parser);
ast_node_t * parser_parse_statement(parser_t * parser);
ast_node_t * parser_parse_id(parser_t * parser);
ast_node_t * parser_parse_expression(parser_t * parser);
ast_node_t * parser_parse_term(parser_t * parser);
ast_node_t * parser_parse_factor(parser_t * parser);
ast_node_t * parser_parse_variable(parser_t * parser);
ast_node_t * parser_parse_variable_definition(parser_t * parser);
ast_node_t * parser_parse_string(parser_t * parser);
ast_node_t * parser_parse_function_call(parser_t * parser);





#endif //PARSER_PARSER_H
