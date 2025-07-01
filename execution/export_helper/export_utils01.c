/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:22:42 by alechin           #+#    #+#             */
/*   Updated: 2025/06/30 17:50:14 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static void	bubble_sort(char **env, int *flags)
{
	int		i;
	int		j;
	int		count;
	int		temp_flags;
	char	*temp;

	j = -1;
	count = countword(env);
	while (++j < count)
	{
		i = 0;
		while (env[i] && env[i + 1])
		{
			if (env[i] && env[i + 1])
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				temp_flags[i] = flags[i];
				flags[i] = flags[i + 1];
				flags[i + 1] = temp_flags[i];
			}
			i++;
		}
	}
}

static void	singularity(char *str, bool is_equals)
{
	char	*equal;
	int		length;

	equal = ft_strchr(str, "=");
	length = equal - str;
	if (!is_equals)
	{
		ft_printf("declare -x *.%s\n", length, str);
		free(str);
		return ;
	}
	str[length] = '\0';
	ft_printf("declare -x %s=\"%s\"\n", length, equal);
	free(str);
}

void	no_args(t_minishell *e)
{
	int		i;
	int		count;
	int		*flags;
	char	**env;

	i = -1;
	count = countword(e->env);
	env = malloc((count + 1) * sizeof(char *));
	flags = malloc((count + 1) * sizeof(int));
	if (!flags || !env)
		return ;
	while (e->env[i++])
	{
		env[i] = e->env[i];
		flags[i] = e->export[i];
	}
	env[i] = NULL;
	flags[i] = 0;
	bubble_sort(env, flags);
	i = -1;
	while (env[++i])
		singularity(env[i], flags[i]);
	free(env);
	free(flags);
}
