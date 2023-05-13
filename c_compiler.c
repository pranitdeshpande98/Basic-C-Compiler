#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKEN_LEN 128

typedef enum {
    TK_PLUS,
    TK_MINUS,
    TK_ASTERISK,
    TK_SLASH,
    TK_INTLIT,
    TK_EOF
} token_t;

typedef struct {
    token_t type;
    char str[MAX_TOKEN_LEN];
    int len;
} token;

int pos = 0;

char input[] = "1+2*3";

token next_token() {
    char ch;
    token tok = { 0 };
    while (input[pos] != '\0') {
        ch = input[pos];
        pos++;

        if (ch == '+') {
            tok.type = TK_PLUS;
            strcpy(tok.str, "+");
            tok.len = 1;
            break;
        } else if (ch == '-') {
            tok.type = TK_MINUS;
            strcpy(tok.str, "-");
            tok.len = 1;
            break;
        } else if (ch == '*') {
            tok.type = TK_ASTERISK;
            strcpy(tok.str, "*");
            tok.len = 1;
            break;
        } else if (ch == '/') {
            tok.type = TK_SLASH;
            strcpy(tok.str, "/");
            tok.len = 1;
            break;
        } else if (isdigit(ch)) {
            int i = 0;
            tok.type = TK_INTLIT;
            while (isdigit(ch)) {
                tok.str[i++] = ch;
                ch = input[pos];
                pos++;
            }
            tok.len = i;
            break;
        }
    }
    if (tok.type == 0) {
        tok.type = TK_EOF;
    }
    return tok;
}

void error(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int main(int argc, char** argv) {
    token tok;
    int left, right, result;
    left = right = result = 0;

    tok = next_token();
    if (tok.type != TK_INTLIT) {
        error("Expected integer literal");
    }
    sscanf(tok.str, "%d", &left);

    tok = next_token();
    if (tok.type != TK_PLUS) {
        error("Expected +");
    }

    tok = next_token();
    if (tok.type != TK_INTLIT) {
        error("Expected integer literal");
    }
    sscanf(tok.str, "%d", &right);

    result = left + right;
    printf("%d\n", result);

    return 0;
}
