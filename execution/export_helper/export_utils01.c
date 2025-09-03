/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:22:42 by alechin           #+#    #+#             */
/*   Updated: 2025/09/03 10:18:30 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static void	swap_env(char **env, int *flags, int i)
{
	char	*temp;
	int		tmp_flag;

	temp = env[i];
	env[i] = env[i + 1];
	env[i + 1] = temp;
	tmp_flag = flags[i];
	flags[i] = flags[i + 1];
	flags[i + 1] = tmp_flag;
}

static void	bubble_sort(char **env, int *flags)
{
	int	i;
	int	j;
	int	count;

	count = countword(env);
	j = 0;
	while (j < count)
	{
		i = 0;
		while (env[i] && env[i + 1])
		{
			if (strcmp(env[i], env[i + 1]) > 0)
				swap_env(env, flags, i);
			i++;
		}
		j++;
	}
}

static void	singularity(char *str)
{
	char	*equal;
	int		len;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		printf("declare -x %s\n", str);
		return ;
	}
	len = equal - str;
	printf("declare -x %.*s=\"%s\"\n", len, str, equal + 1);
}

void	no_args(t_minishell *e)
{
	int		i;
	int		count;
	int		*flags;
	char	**env;

	count = countword(e->env);
	env = malloc((count + 1) * sizeof(char *));
	flags = malloc((count + 1) * sizeof(int));
	if (!env || !flags)
		return ;
	i = -1;
	while (e->env[++i])
	{
		env[i] = e->env[i];
		flags[i] = e->export[i];
	}
	env[i] = NULL;
	flags[i] = 0;
	bubble_sort(env, flags);
	i = -1;
	while (env[++i])
		singularity(env[i]);
	free(env);
	free(flags);
}

void	export_pwd_var(t_minishell *e, char *prefix, char *value)
{
	char	*joined;
	char	*variables;

	joined = ft_strjoin(prefix, value);
	if (!joined)
		return ;
	variables = ft_strdup(joined);
	if (!variables)
	{
		free(joined);
		return ;
	}
	koi_export(e, &variables);
	free(joined);
	free(variables);
}
