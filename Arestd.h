//
// Created by emanuele on 17/05/24.
//

#ifndef PARSER_ARESTD_H
#define PARSER_ARESTD_H
#include "AST.h"
#include "scope.h"
void ares_print(scope_t* scope, ast_node_t *function_tree);
void ares_println(scope_t* scope, ast_node_t *function_tree);


#endif //PARSER_ARESTD_H
