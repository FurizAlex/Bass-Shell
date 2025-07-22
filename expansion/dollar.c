/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:52:13 by alechin           #+#    #+#             */
/*   Updated: 2025/07/21 16:40:23 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static char	*invalid(char *prefix, char *dollar, t_root *root)
{
	char	*literal;
	char	*temp;
	char	*res;

	literal = ft_strdup("$");
	temp = ft_strjoin(prefix, literal);
	res = ft_strjoin(temp, expand_dollar(dollar, root));
	free(literal);
	free(temp);
	return (res);
}

static char	*valid(char *prefix, char *dollar, t_root *root)
{
	int		len;
	char	*end;
	char	*res;
	char	*temp;
	char	*env_value;

	end = NULL;
	if (*(dollar + 1) == '?')
	{
		len = 1;
		env_value = ft_itoa(root->msh->status);
	}
	else
	{
		len = variable_len(dollar + 1);
		env_value = to_get_env(dollar + 1, len);
	}
	temp = ft_strjoin(prefix, env_value);
	res = ft_strjoin(temp, expand_dollar(dollar, root));
	free(prefix);
	free(temp);
	free(end);
	return (res);
}

char	*expand_dollar(char *prompt, t_root *root)
{
	char	*res;
	char	*dollar;
	char	*prefix;

	dollar = ft_strchr(prompt, '$');
	prefix = dupnxtra(prompt, dollar - prompt);
	if (!dollar)
		return (ft_strdup(dollar));
	res = invalid(prefix, dollar, root);
	if (*(dollar + 1) != '\0' || valid_env_ch(*(dollar + 1)))
		valid(prefix, dollar, root);
	return (res);
}
