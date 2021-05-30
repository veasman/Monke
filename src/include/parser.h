#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "AST.h"

typedef struct PARSER_STRUCT {
    lexer_t* lexer;
    token_t* current_token;
}parser_t;

parser_t* init_parser(lexer_t* lexer);

void parser_eat(parser_t* parser, int token_type);

AST_T* parser_parse(parser_t* parser);

AST_T* parser_parse_statement(parser_t* parser);

AST_T* parser_parse_statements(parser_t* parser);

AST_T* parser_parse_expression(parser_t* parser);

AST_T* parser_parse_factor(parser_t* parser);

AST_T* parser_parse_term(parser_t* parser);

AST_T* parser_parse_function_call(parser_t* parser);

AST_T* parser_parse_variable(parser_t* parser);

AST_T* parser_parse_variable_definition(parser_t* parser);

AST_T* parser_parse_string(parser_t* parser);

AST_T* parser_parse_id(parser_t* parser);
#endif

