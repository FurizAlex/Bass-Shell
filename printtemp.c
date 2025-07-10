/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtemp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:48:52 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/08 16:30:34 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*

void print_ast(t_ast_node *node, int depth) {
    if (!node)
        return;

    const char *type_names[] = {
        "COMMAND", "PIPE", "REDIRECT_IN", "REDIRECT_OUT",
        "REDIRECT_APPEND", "HEREDOC"
    };

    // Print indentation
    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%s", type_names[node->type]);

    if (node->type == NODE_COMMAND && node->args) {
        printf(" [");
        for (int i = 0; node->args[i]; i++) {
            printf("%s", node->args[i]);
            if (node->args[i + 1])
                printf(", ");
        }
        printf("]");
    }

    if (node->filename) {
        printf(" -> %s", node->filename);
    }

    printf("\n");

    // Print children
    if (node->left) {
        for (int i = 0; i < depth + 1; i++)
            printf("  ");
        printf("LEFT:\n");
        print_ast(node->left, depth + 2);
    }

    if (node->right) {
        for (int i = 0; i < depth + 1; i++)
            printf("  ");
        printf("RIGHT:\n");
        print_ast(node->right, depth + 2);
    }
}

*/