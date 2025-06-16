/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:08:21 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/13 01:27:25 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static bool	is_special(t_lexer *lexer)
{
	char	c;

	c = lexer->current_char;
	return ((c == '|' || c == '<' || c == '>')
		&& !lexer->in_single_quote && !lexer->in_double_quote);
}

static bool	is_breaking_whitespace(t_lexer *lexer)
{
	return (ft_isspace(lexer->current_char)
		&& !lexer->in_single_quote && !lexer->in_double_quote);
}

static bool	handle_quotes(t_lexer *lexer, char *word, int *len)
{
	if (lexer->current_char == '\'' && !lexer->in_double_quote)
	{
		lexer->in_single_quote = !lexer->in_single_quote;
		word[(*len)++] = lexer->current_char;
		advance_lexer(lexer);
		return (true);
	}
	if (lexer->current_char == '"' && !lexer->in_single_quote)
	{
		lexer->in_double_quote = !lexer->in_double_quote;
		word[(*len)++] = lexer->current_char;
		advance_lexer(lexer);
		return (true);
	}
	return (false);
}

static bool	handle_dollar(t_lexer *lexer, char *word, int *len, bool *exp)
{
	if (lexer->current_char == '$' && !lexer->in_single_quote)
	{
		*exp = true;
		word[(*len)++] = lexer->current_char;
		advance_lexer(lexer);
		return (true);
	}
	return (false);
}

t_token	*read_word(t_lexer *lexer)
{
	char	*word;
	int		word_len;
	bool	has_expansion;

	word = malloc(1024);
	word_len = 0;
	has_expansion = false;
	if (!word)
		return (NULL);
	while (lexer->current_char != '\0')
	{
		if (handle_quotes(lexer, word, &word_len))
			continue ;
		if (handle_dollar(lexer, word, &word_len, &has_expansion))
			continue ;
		if (is_breaking_whitespace(lexer) || is_special(lexer))
			break ;
		word[word_len++] = lexer->current_char;
		advance_lexer(lexer);
	}
	word[word_len] = '\0';
	if (word_len == 0)
		return (free(word), NULL);
	return (create_token(TOKEN_WORD, word, has_expansion));
}