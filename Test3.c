#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 8
#define MAX_OPERATORS 12
#define MAX_TOKEN_LENGTH 100

// Define keywords and operators
const char *keywords[MAX_KEYWORDS] = {"int", "float", "if", "else", "while", "for", "return", "void"};
const char *operators[MAX_OPERATORS] = {"+", "-", "*","/", "=", "==", "!=", "<", ">", "<=", ">=", "&&"};

// Function to check if a token is a keyword
int is_keyword(const char *token) {
	int i;
    for(i=0;i<MAX_KEYWORDS;i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a token is an operator
int is_operator(const char *token) {
	int i;
    for(i=0;i<MAX_OPERATORS;i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to classify tokens
const char* classify_token(const char *token) {
    if (is_keyword(token)) {
        return "Keyword";
    } else if (is_operator(token)) {
        return "Operator";
    } else if (isalpha(token[0]) || token[0] == '_') {
        return "Identifier";
    } else {
        return "Unknown";
    }
}

// Function to perform lexical analysis
void lexical_analyzer(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Input file not found. Please check the file path.\n");
        return;
    }

    char content[MAX_TOKEN_LENGTH * 100];
    char token[MAX_TOKEN_LENGTH];
    int index = 0;

    // Read the file content
    fread(content, sizeof(char), sizeof(content) - 1, file);
    fclose(file);

    // Process the content
    printf("Token\t\tType\n");
    printf("---------------------\n");
     int i;
    for(i=0;content[i]!='\0';i++) {
        char c = content[i];
        if (isspace(c) || strchr("+-*/=<>!&|", c)) {
            if (index > 0) {
                token[index] = '\0';
                printf("%s\t\t%s\n", token, classify_token(token));
                index = 0;
            }
            if (strchr("+-*/=<>!&|", c)) {
                char operator_token[3] = {c, '\0', '\0'};
                if (strchr("=<>!&|", content[i + 1]) && content[i + 1] == '=') {
                    operator_token[1] = content[++i];
                }
                printf("%s\t\t%s\n", operator_token, classify_token(operator_token));
            }
        } else {
            token[index++] = c;
        }
    }

    if (index > 0) {
        token[index] = '\0';
        printf("%s\t\t%s\n", token, classify_token(token));
    }
}

// Main function
int main() {
    const char *input_file = "input.txt"; // Replace with your input file path
    lexical_analyzer(input_file);
    return 0;
}
