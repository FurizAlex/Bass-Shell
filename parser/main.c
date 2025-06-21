#include "../includes/parsing.h"

int main(void) {
    // Test cases focused on quote removal
    char *test_cases[] = {
        "echo hello",                    // No quotes
        "echo 'hello world'",           // Single quotes - should remove quotes
        "echo \"hello world\"",         // Double quotes - should remove quotes
        "echo 'hello'",                 // Single word in quotes
        "echo \"hello\"",               // Single word in double quotes
        "echo 'hello world' test",      // Quoted + unquoted
        "echo \"hello\" world",         // Mixed tokens
        "echo 'single' \"double\"",     // Both quote types
        "echo \"hello\"world",          // Quote concatenation
        "echo 'it\\'s a test'",         // Escaped quote (complex case)
        "echo \"\"",                    // Empty double quotes
        "echo ''",                      // Empty single quotes
        "echo 'preserve    spaces'",    // Spaces in quotes should be preserved
        "echo \"preserve    spaces\"",  // Spaces in double quotes
        "echo '$HOME'",                 // $ in single quotes (no expansion)
        "echo \"$HOME\"",               // $ in double quotes (should mark expansion)
        "echo $HOME",                   // $ without quotes (should mark expansion)
        NULL
    };

    printf("=== QUOTE REMOVAL TESTING ===\n");
    for (int i = 0; test_cases[i]; i++) {
        printf("\n--- Input: %s ---\n", test_cases[i]);
        t_token *tokens = tokenize(test_cases[i]);

        printf("Expected behavior:\n");
        if (strstr(test_cases[i], "'hello world'")) {
            printf("  Token: 'hello world' -> 'hello world' (quotes removed)\n");
        }
        if (strstr(test_cases[i], "\"hello world\"")) {
            printf("  Token: \"hello world\" -> 'hello world' (quotes removed)\n");
        }

        printf("Actual tokens:\n");
        print_tokens(tokens);
        free_tokens(tokens);
    }

    return 0;
}