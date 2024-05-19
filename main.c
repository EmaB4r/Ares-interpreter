#include "lexer.h"
#include "io.h"
#include <stdio.h>
#include "AST.h"
#include <string.h>
#include "parser.h"
#include "visitor.h"


void print_tree(ast_node_t * root){
    if(root!=NULL){
        printf("(");
        print_tree(root->left);
        printf(" %s ", root->token->value);
        print_tree(root->right);
        printf(")");
    }
}


int eval(ast_node_t * root){
    if(root->type==AST_DIGIT)
        return strtol(root->token->value, NULL, 10);
    if (!strcmp("+", root->token->value)) {
        return eval(root->left) + eval(root->right);
    }
    if (!strcmp("-", root->token->value)) {
        return eval(root->left) - eval(root->right);
    }
    if (!strcmp("*", root->token->value)) {
        return eval(root->left) * eval(root->right);
    }
    if (!strcmp("/", root->token->value)) {
        return eval(root->left) / eval(root->right);
    }
}

int main(int argc, char const *argv[])
{
    char* source_code = get_file_text_from_path("../main.ares");
    lexer_t * lexer= lexer_init(source_code);

    parser_t * parser = parser_init(lexer);
    parser_parse(parser);
    visitor_visit_parser(parser);


    return 0;
}
