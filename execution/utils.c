/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:27:41 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/19 16:21:08 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Literally exist for norminette reasons */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	copy_existing_env(t_minishell *e, char **env_copy, int *flag_copy)
{
	int	i;

	i = 0;
	while (e->env[i])
	{
		env_copy[i] = ft_strdup(e->env[i]);
		if (!env_copy[i])
			return (0);
		flag_copy[i] = e->export[i];
		i++;
	}
	return (1);
}

int	rec_left(t_root **root, t_micro shell, t_token **token, t_root *new)
{
	int	err;

	err = recursive_tree(root,
			micro_editor(shell, new->tokens[0], false), token, false);
	if (err != UNDECLARED)
		return (err);
	return (UNDECLARED);
}

int	rec_right(t_root **root, t_micro shell, t_token **token, t_root *new)
{
	int	err;

	err = recursive_tree(root,
			micro_editor(shell, new->tokens[0], true), token, true);
	if (err != UNDECLARED)
		return (err);
	return (UNDECLARED);
}

int	count_length(t_token *token)
{
	int	len;

	len = 0;
	while (token)
	{
		len++;
		token = token->next;
	}
	return (len);
}

void	print_ast_error(int err)
{
	if (err == MEMORY)
		ft_putstr_fd("\x1b[0;31mError: Malloc\x1b[0m\n", 2);
	else if (err == REDIRECTION)
		ft_putstr_fd("\x1b[0;31mError: Incorrect Redirect Use\x1b[0m\n", 2);
	else if (err == PIPE)
		ft_putstr_fd("\x1b[0;31mError: Incorrect Pipe Use\x1b[0m\n", 2);
}
