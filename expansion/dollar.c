/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:52:13 by alechin           #+#    #+#             */
/*   Updated: 2025/07/09 17:55:14 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static bool	has_question_mark(char	*dollar, t_minishell *msh)
{
	int			length;
	char		*env_value;

	if (*(dollar + 1) == '?')
	{
		length = 1;
		env_value = ft_itoa(msh->status);
		return (true);
	}
	return (false);
}

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
	len = variable_len(dollar + 1);
	env_value = to_get_env(dollar + 1, len);
	temp = ft_strjoin(prefix, env_value);
	res = ft_strjoin(temp, expand_dollar(dollar, root));
	free(prefix);
	free(temp);
	free(end);
	return (res);
}

char	*expand_dollar(char *prompt, t_root *root)
{
	int		i;
	char	*res;
	char	*dollar;
	char	*prefix;
	bool	is_valid;

	i = 0;
	is_valid = false;
	dollar = ft_strchr(prompt, '$');
	prefix = dupnxtra(prompt, dollar - prompt);
	if (!dollar)
		return (ft_strdup(dollar));
	res = invalid(prefix, dollar, root);
	if (*(dollar + 1) != '\0' || valid_env_ch(*(dollar + 1)))
	{
		if (has_question_mark(dollar, root->msh))
			valid(prefix, dollar, root);
	}
	return (res);
}
