
#include "../includes/parsing.h"

int main(void) {
    // Test cases
    char *test_cases[] = {
        "ls -la",
        "echo 'hello world'",
        "cat file.txt | grep pattern",
        "echo \"Hello $USER\"",
        "command > output.txt",
        "cat < input.txt >> output.txt",
        "grep pattern << EOF",
        "echo $HOME && ls",
        "echo 'single quotes' \"double quotes\"",
        "command with    multiple   spaces",
        NULL
    };

    for (int i = 0; test_cases[i]; i++) {
        printf("\n--- Testing: %s ---\n", test_cases[i]);
        t_token *tokens = tokenize(test_cases[i]);
        print_tokens(tokens);
        free_tokens(tokens);
    }

    return 0;
}