/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:52:13 by alechin           #+#    #+#             */
/*   Updated: 2025/06/24 14:01:26 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static bool	has_question_mark(char	*dollar)
{
	char		*length;
	char		*env_value;
	t_minishell	*msh;

	if (*(dollar + 1) == '?')
	{
		length = 1;
		env_value = ft_itoa(msh->status);
		return (true);
	}
	return (false);
}

static char	*invalid(char *prefix, char *dollar)
{
	char	*literal;
	char	*temp;
	char	*res;

	literal = ft_strdup("$");
	temp = ft_strjoin(prefix, literal);
	res = ft_strjoin(temp, expand_dollar(dollar));
	free(literal);
	free(temp);
	return (res);
}

static char	*valid(char *prefix, char *dollar)
{
	int		len;
	char	*end;
	char	*res;
	char	*temp;
	char	*env_value;

	len = variable_len(dollar + 1);
	env_value = to_get_env(dollar + 1, len);
	temp = ft_strjoin(prefix, env_value);
	res = ft_strjoin(temp, expand_dollar(dollar));
	free(prefix);
	free(temp);
	free(tail);
	return (res);
}

char	*expand_dollar(char *prompt)
{
	int		i;
	char	*res;
	char	*dollar;
	char	*prefix;
	bool	is_valid;

	i = 0;
	is_valid = false;
	prefix = dupnxtra(prompt, dollar - prompt);
	dollar = ft_strchr(prompt, '$');
	if (!dollar)
		return (ft_strdup(cmd));
	res = invalid(prefix, dollar);
	if (*(dollar + 1) != '\0' || valid_env_ch(*(dollar + 1)))
	{
		if (has_question_mark(dollar, root->msh))
			valid(prefix, dollar);
	}
	return (res);
}
