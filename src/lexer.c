#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

lexer_t* init_lexer(char* contents) {
    lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void lexer_advance(lexer_t* lexer) {
    // Go to next letter/word
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_t* lexer) {
    // Avoid whitespace when going through code
    while (lexer->c == ' ' || lexer->c == 10) {
        lexer_advance(lexer);
    }
}

token_t* lexer_get_next_token(lexer_t* lexer) {
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        // Check for whitespace
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);

        // Check if char is alphanumeric
        if (isalnum(lexer->c))
            return lexer_collect_id(lexer);

        // We could put this in the switch statement but it's working so eh
        if (lexer->c == '"')
            return lexer_collect_string(lexer);

        // Check for important chars
        switch (lexer->c) {
            case '=': return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer))); break;
            case ';': return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer))); break;
            case '(': return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))); break;
            case ')': return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))); break;
        }
    }

    return (void*)0;
}

token_t* lexer_collect_string(lexer_t* lexer) {
    // Advance to next string
    lexer_advance(lexer);

    // Allocate a string in memory
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    // If current char is not a quote
    while (lexer->c != '"') {
        // Get as string
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        // Map value to s
        strcat(value, s);

        // Advance to next char
        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(TOKEN_STRING, value);
}

token_t* lexer_collect_id(lexer_t* lexer) {
    // Allocate a string in memory
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    // isalnum = Is alpha numeric
    while (isalnum(lexer->c)) {
        // Get next word as string
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        // Advace past current string
        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, value);
}

token_t* lexer_advance_with_token(lexer_t* lexer, token_t* token) {
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(lexer_t* lexer) {
    // Create a new char array "str" to get turn chars into a string
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}

