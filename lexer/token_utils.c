/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:57:53 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/01 17:20:46 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->current_char != '\0'
		&& ft_isspace(lexer->current_char)
		&& !lexer->in_single_quote
		&& !lexer->in_double_quote)
	{
		advance_lexer(lexer);
	}
}

/* Allocates token struct, sets type/value/expansion flag,
duplicates string values*/
t_token	*create_token(t_token_type type, char *value, bool has_expansion)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = lexers();
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->lexer = lexer;
	token->has_expansion = has_expansion;
	token->next = NULL;
	return (token);
}

/*Main tokenizer dispatcher:
skips whitespace → identifies token type → calls appropriate reader*/
t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->current_char != '\0')
	{
		if (ft_isspace(lexer->current_char)
			&& !lexer->in_single_quote
			&& !lexer->in_double_quote)
		{
			skip_whitespace(lexer);
			continue ;
		}
		if (lexer->current_char == '|'
			&& !lexer->in_single_quote
			&& !lexer->in_double_quote)
		{
			advance_lexer(lexer);
			return (create_token(TOKEN_PIPE, "|", false));
		}
		if ((lexer->current_char == '<' || lexer->current_char == '>')
			&& !lexer->in_single_quote && !lexer->in_double_quote)
			return (read_redirect(lexer));
		return (read_word(lexer));
	}
	return (create_token(TOKEN_EOF, NULL, false));
}

/*deallocates token linked list im getting tired of being formal*/
void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free (temp->value);
		free(temp);
	}
}

/*TEMPORARY MEASURE SO THAT WE CAN CONFIRM IT WORKS
void	print_tokens(t_token *tokens)
{
	t_token		*current;
	const char	*type_names[] = {"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT",
		"REDIRECT_APPEND", "HEREDOC", "EOF", "ERROR"};

	current = tokens;
	printf("=== TOKENS ===\n");
	while (current) {
        printf("Type: %-15s Value: '%s'",
               type_names[current->type],
               current->value ? current->value : "NULL");
        if (current->has_expansion)
            printf(" [HAS_EXPANSION]");
        printf("\n");
        current = current->next;
    }
    printf("==============\n");
}*/