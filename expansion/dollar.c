/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:52:13 by alechin           #+#    #+#             */
/*   Updated: 2025/09/02 10:31:24 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static char	*expand_question(char *prefix, char *rest, t_minishell *msh)
{
	char		*num;
	char		*tmp;
	char		*suf;
	char		*r;
	int			status;

	msh = minishell();
	status = 0;
	if (msh)
		status = msh->last_status;
	num = ft_itoa(status);
	if (!num)
		return (free(prefix), NULL);
	tmp = ft_strjoin(prefix, num);
	free(num);
	if (!tmp)
		return (NULL);
	suf = expand_dollar(rest, msh);
	if (!suf)
		return (free(tmp), NULL);
	r = ft_strjoin(tmp, suf);
	return (free(tmp), free(suf), r);
}

static char	*expand_var(char *prefix, char *dollar, int vlen)
{
	char	*value;
	char	*valdup;
	char	*tmp;
	char	*suf;
	char	*r;

	value = to_get_env(dollar + 1, vlen, minishell());
	if (value)
		valdup = ft_strdup(value);
	else
		valdup = ft_strdup("");
	if (!valdup)
		return (free(prefix), NULL);
	tmp = join_free_both(prefix, valdup);
	if (!tmp)
		return (NULL);
	suf = expand_dollar(dollar + 1 + vlen, minishell());
	if (!suf)
		return (free(tmp), NULL);
	r = ft_strjoin(tmp, suf);
	return (free(tmp), free(suf), r);
}

static char	*expand_literal_dollar(char *prefix, char *dollar)
{
	char	*tmp;
	char	*rest;
	char	*r;

	tmp = ft_strjoin(prefix, "$");
	free(prefix);
	if (!tmp)
		return (NULL);
	rest = expand_dollar(dollar + 1, minishell());
	if (!rest)
		return (free(tmp), NULL);
	r = ft_strjoin(tmp, rest);
	return (free(tmp), free(rest), r);
}

static char	*handle_special_cases(char *prefix, char *dollar)
{
	char		*r;
	int			vlen;
	t_minishell	*msh;

	msh = minishell();
	if (*(dollar + 1) == '\0')
	{
		r = ft_strjoin(prefix, "$");
		return (free(prefix), r);
	}
	if (*(dollar + 1) == '?')
		return (expand_question(prefix, dollar + 2, msh));
	vlen = variable_len(dollar + 1);
	if (vlen == 0)
		return (expand_literal_dollar(prefix, dollar));
	return (expand_var(prefix, dollar, vlen));
}

char	*expand_dollar(char *prompt, t_minishell *msh)
{
	char	*dollar;
	char	*prefix;

	(void)msh;
	if (!prompt)
		return (NULL);
	if (is_single_quoted_literal(prompt) == true)
		return (dupnxtra(prompt + 1, ft_strlen(prompt) - 2));
	dollar = ft_strchr(prompt, '$');
	if (!dollar)
		return (ft_strdup(prompt));
	prefix = dupnxtra(prompt, dollar - prompt);
	if (!prefix)
		return (NULL);
	return (handle_special_cases(prefix, dollar));
}
