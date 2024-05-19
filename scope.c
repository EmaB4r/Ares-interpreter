//
// Created by emanuele on 17/05/24.
//

#include "scope.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
scope_t * scope_init(){
    scope_t * s= calloc(1,sizeof (scope_t));
    return s;
}

void scope_add_variable(scope_t * scope, token_t * token_variable_name, token_t * token_variable_value){
    if(scope->total_variables){
        scope->variable_name= realloc(scope->variable_name, sizeof(token_t *)*(scope->total_variables+1));
        scope->variable_value= realloc(scope->variable_value, sizeof(token_t *)*(scope->total_variables+1));
    }
    else{
        scope->variable_name= malloc(sizeof(token_t *));
        scope->variable_value= malloc(sizeof(token_t *));
    }
    scope->variable_name[scope->total_variables]=token_variable_name;
    scope->variable_value[scope->total_variables]=token_variable_value;
    scope->total_variables++;
}
void scope_update_variable(scope_t * scope, token_t * token_variable_name, token_t * token_variable_value){
    int i=0;
    for (i=0; i<scope->total_variables && strcmp(scope->variable_name[i]->value, token_variable_name->value) ; i++);
    if(i<scope->total_variables){
        scope->variable_value[i]=token_variable_value;
        return;
    }
    printf("\n\nSCOPE ERROR\nvariable '%s' is NOT defined\n", token_variable_name->value);
    exit(1);
}


token_t *  scope_get_variable_value(scope_t * scope, token_t * token_variable_name){
    int i=0;
    for (i=0; i<scope->total_variables && strcmp(scope->variable_name[i]->value, token_variable_name->value) ; i++);
    if(i<scope->total_variables)
        return scope->variable_value[i];
    printf("\n\nSCOPE ERROR\nvariable '%s' is NOT defined\n", token_variable_name->value);
    exit(1);
}