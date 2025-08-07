/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:52:13 by alechin           #+#    #+#             */
/*   Updated: 2025/08/07 09:44:39 by furizalex        ###   ########.fr       */
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
	free(literal);
	res = ft_strjoin(temp, expand_dollar(dollar, root));
	free(temp);
	return (res);
}

static char	*valid(char *prefix, char *dollar, t_root *root)
{
	int		len;
	char	*res;
	char	*temp;
	char	*env_value;

	if (*(dollar + 1) == '?')
	{
		len = 1;
		env_value = ft_itoa(root->msh->status);
	}
	else
	{
		len = variable_len(dollar + 1);
		env_value = to_get_env(dollar + 1, len, root);
	}
	if (!env_value)
		env_value = ft_strdup("");
	else
		env_value = ft_strdup(env_value);
	temp = ft_strjoin(prefix, env_value);
	free(env_value);
	res = ft_strjoin(temp, expand_dollar(dollar + 1 + len, root));
	free(prefix);
	free(temp);
	return (res);
}

char	*expand_dollar(char *prompt, t_root *root)
{
	char	*res;
	char	*dollar;
	char	*prefix;
	char	*temp_res;
	char	*temp_prefix;

	dollar = ft_strchr(prompt, '$');
	if (!dollar)
		return (ft_strdup(prompt));
	prefix = dupnxtra(prompt, dollar - prompt);
	if (!prefix)
		return (NULL);
	res = invalid(prefix, dollar, root);
	if (!res)
	{
		free(prefix);
		return (NULL);
	}
	if (*(dollar + 1) != '\0' || valid_env_ch(*(dollar + 1)))
	{
		temp_res = valid(prefix, dollar, root);
		free(res);
		res = temp_res;
		if (!res)
		{
			free(prefix);
			return (NULL);
		}
	}
	else
	{
		temp_prefix = prefix;
		prefix = ft_strjoin(temp_prefix, "$");
		free(temp_prefix);
		if (!prefix)
		{
			free(res);
			return (NULL);
		}
		char *remaining = expand_dollar(dollar + 1, root);
		char *final_res = ft_strjoin(prefix, remaining);
		free(prefix);
		free(remaining);
		free(res);
		res = final_res;
	}
	return (res);
}
