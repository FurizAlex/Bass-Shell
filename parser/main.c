#include "../includes/parsing.h"

int main(void) {
    // Example test cases showing the tree structure
    printf("=== PARSER EXAMPLES ===\n\n");

    printf("Command: 'ls -la'\n");
    printf("AST Structure:\n");
    printf("  COMMAND [ls, -la]\n\n");

    printf("Command: 'cat file.txt | grep pattern'\n");
    printf("AST Structure:\n");
    printf("  PIPE\n");
    printf("    LEFT:\n");
    printf("      COMMAND [cat, file.txt]\n");
    printf("    RIGHT:\n");
    printf("      COMMAND [grep, pattern]\n\n");

    printf("Command: 'cat < input.txt > output.txt'\n");
    printf("AST Structure:\n");
    printf("  REDIRECT_OUT -> output.txt\n"); 
    printf("    LEFT:\n");
    printf("      REDIRECT_IN -> input.txt\n");
    printf("        LEFT:\n");
    printf("          COMMAND [cat]\n\n");

    printf("Command: 'ls | grep pattern > results.txt'\n");
    printf("AST Structure:\n");
    printf("  PIPE\n");
    printf("    LEFT:\n");
    printf("      COMMAND [ls]\n");
    printf("    RIGHT:\n");
    printf("      REDIRECT_OUT -> results.txt\n");
    printf("        LEFT:\n");
    printf("          COMMAND [grep, pattern]\n\n");

    return 0;
}