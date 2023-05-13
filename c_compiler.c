#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_INTEGER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
} TokenKind;

typedef struct {
    TokenKind kind;
    const char* start;
    int length;
    int value;
} Token;

typedef struct {
    const char* start;
    int length;
} Tokenizer;

void error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void tokenizer_init(Tokenizer* tokenizer, const char* input) {
    tokenizer->start = input;
    tokenizer->length = strlen(input);
}

int tokenizer_next(Tokenizer* tokenizer, Token* token) {
    while (tokenizer->start < tokenizer->start + tokenizer->length) {
        switch (*tokenizer->start) {
            case '+':
                token->kind = TOKEN_PLUS;
                token->start = tokenizer->start;
                token->length = 1;
                tokenizer->start++;
                return 1;
            case '-':
                token->kind = TOKEN_MINUS;
                token->start = tokenizer->start;
                token->length = 1;
                tokenizer->start++;
                return 1;
            case '*':
                token->kind = TOKEN_STAR;
                token->start = tokenizer->start;
                token->length = 1;
                tokenizer->start++;
                return 1;
            case '/':
                token->kind = TOKEN_SLASH;
                token->start = tokenizer->start;
                token->length = 1;
                tokenizer->start++;
                return 1;
            case '(':
                token->kind = TOKEN_LPAREN;
                token->start = tokenizer->start;
                token->length = 1;
                tokenizer->start++;
                return 1;
            case ')':
                token->kind = TOKEN_RPAREN;
                token->start = tokenizer->start;
                token->length = 1;
                tokenizer->start++;
                return 1;
            default:
                if (*tokenizer->start >= '0' && *tokenizer->start <= '9') {
                    token->kind = TOKEN_INTEGER;
                    token->start = tokenizer->start;
                    token->length = 1;
                    token->value = *tokenizer->start - '0';
                    tokenizer->start++;
                    while (*tokenizer->start >= '0' && *tokenizer->start <= '9') {
                        token->length++;
                        token->value *= 10;
                        token->value += *tokenizer->start - '0';
                        tokenizer->start++;
                    }
                    return 1;
                } else {
                    error("Invalid token");
                }
        }
    }
    token->kind = TOKEN_EOF;
    token->start = tokenizer->start;
    token->length = 0;
    return 0;
}

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        error("Usage: compiler <input-file>");
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        error("Cannot open input file");
    }

    fseek(file
