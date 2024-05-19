//
// Created by emanuele on 17/05/24.
//

#ifndef PARSER_VISITOR_H
#define PARSER_VISITOR_H
#include "AST.h"
#include "parser.h"
#include "scope.h"

void visitor_visit_parser(parser_t * parser);

void visitor_visit(scope_t * scope, ast_node_t* node);

void visitor_visit_variable_definition(scope_t * scope, ast_node_t* node);

void visitor_visit_function_definition(scope_t * scope, ast_node_t* node);

void visitor_visit_variable(scope_t * scope, ast_node_t* node);

void visitor_visit_function_call(scope_t * scope, ast_node_t* node);

void visitor_visit_string(scope_t * scope, ast_node_t* node);

void visitor_visit_compound(scope_t * scope, ast_node_t* node);
#endif //PARSER_VISITOR_H
