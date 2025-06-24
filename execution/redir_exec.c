/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:56 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 15:17:38 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int redir_type(int type)
{
	return (type == TOKEN_REDIRECT_IN
		|| TOKEN_REDIRECT_OUT
		|| TOKEN_REDIRECT_APPEND
		|| TOKEN_HEREDOC);
}

int	redirection(t_redir *redir, t_token *token)
{
	int		types;
	char	*filename;
	char	*quote_filename;

	types = NULL;
	filename = NULL;
	if (token->type != TOKEN_HEREDOC)
	{
		expand_string(filename);
		remove_quotes(filename);
		free(filename);
	}
	if (token->type == TOKEN_REDIRECT_IN)
		types = in(filename);
	if (token->type == TOKEN_REDIRECT_OUT)
		types = out(filename);
	if (token->type == TOKEN_REDIRECT_APPEND)
		types = append(filename);
	if (token->type == TOKEN_HEREDOC)
		types = heredoc(filename, redir->type);
	free(filename);
	return (types);
}