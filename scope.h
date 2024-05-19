//
// Created by emanuele on 17/05/24.
//

#ifndef PARSER_SCOPE_H
#define PARSER_SCOPE_H
#include "token.h"

typedef struct scope_struct{
    token_t ** variable_name;
    token_t ** variable_value;
    long total_variables;
}scope_t;



scope_t * scope_init();
void scope_add_variable(scope_t * scope, token_t * token_variable_name, token_t * token_variable_value);
void scope_update_variable(scope_t * scope, token_t * token_variable_name, token_t * token_variable_value);
token_t *  scope_get_variable_value(scope_t * scope, token_t * token_variable_name);



#endif //PARSER_SCOPE_H
