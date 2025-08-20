/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:52:13 by alechin           #+#    #+#             */
/*   Updated: 2025/08/19 16:56:44 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static char	*expand_question(char *prefix, t_root *root, char *rest)
{
	char	*num;
	char	*tmp;
	char	*suf;
	char	*r;
	int		status;

	status = 0;
	if (root && root->msh)
		status = root->msh->last_status;
	num = ft_itoa(status);
	if (!num)
		return (free(prefix), NULL);
	tmp = ft_strjoin(prefix, num);
	if (free(num), !tmp)
		return (NULL);
	suf = expand_dollar(rest, root);
	if (!suf)
		return (free(tmp), NULL);
	r = ft_strjoin(tmp, suf);
	return (free(tmp), free(suf), r);
}

static char	*expand_var(char *prefix, char *dollar, int vlen, t_root *root)
{
	char	*value;
	char	*valdup;
	char	*tmp;
	char	*suf;
	char	*r;

	value = to_get_env(dollar + 1, vlen, root);
	if (value)
		valdup = ft_strdup(value);
	else
		valdup = ft_strdup("");
	if (!valdup)
		return (free(prefix), NULL);
	tmp = join_free_both(prefix, valdup);
	if (!tmp)
		return (NULL);
	suf = expand_dollar(dollar + 1 + vlen, root);
	if (!suf)
		return (free(tmp), NULL);
	r = ft_strjoin(tmp, suf);
	return (free(tmp), free(suf), r);
}

static char	*expand_literal_dollar(char *prefix, char *dollar, t_root *root)
{
	char	*tmp;
	char	*rest;
	char	*r;

	tmp = ft_strjoin(prefix, "$");
	if (free(prefix), !tmp)
		return (NULL);
	rest = expand_dollar(dollar + 1, root);
	if (!rest)
		return (free(tmp), NULL);
	r = ft_strjoin(tmp, rest);
	return (free(tmp), free(rest), r);
}

static char	*handle_special_cases(char *prefix, char *dollar, t_root *root)
{
	char	*r;
	int		vlen;

	if (*(dollar + 1) == '\0')
	{
		r = ft_strjoin(prefix, "$");
		return (free(prefix), r);
	}
	if (*(dollar + 1) == '?')
		return (expand_question(prefix, root, dollar + 2));
	vlen = variable_len(dollar + 1);
	if (vlen == 0)
		return (expand_literal_dollar(prefix, dollar, root));
	return (expand_var(prefix, dollar, vlen, root));
}

char	*expand_dollar(char *prompt, t_root *root)
{
	char	*dollar;
	char	*prefix;

	if (!prompt)
		return (NULL);
	dollar = ft_strchr(prompt, '$');
	if (!dollar)
		return (ft_strdup(prompt));
	prefix = dupnxtra(prompt, dollar - prompt);
	if (!prefix)
		return (NULL);
	return (handle_special_cases(prefix, dollar, root));
}
