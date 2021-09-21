#include <stdio.h>
#include <string.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

#define MAX_LIMIT 20

void print_help() {
    printf("Usage:\nmonke.out <file>\n:");
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            int len = strlen(argv[i]);
            char* file_ext = &argv[i][len-6];

            if (strcmp(file_ext, ".monke") == 0) {
                lexer_t* lexer = init_lexer(get_file_contents(argv[i]));
                parser_t* parser = init_parser(lexer);
                AST_T* root = parser_parse(parser, parser->scope);
                visitor_t* visitor = init_visitor();
                visitor_visit(visitor, root);
            }
            else {
                print_help();
            }
        }
    }
    else {
        char input[MAX_LIMIT];
        while (1) {
            printf("Welcome to the monke language\n\n- veasman\n");
            fgets(input,MAX_LIMIT, stdin);
            lexer_t* lexer = init_lexer(input);
            parser_t* parser = init_parser(lexer);
            AST_T* root = parser_parse(parser, parser->scope);
            visitor_t* visitor = init_visitor();
            visitor_visit(visitor, root);
        }
    }
    return 0;
}

