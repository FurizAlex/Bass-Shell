/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:04:23 by furizalex         #+#    #+#             */
/*   Updated: 2025/08/11 16:48:14 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "libft.h"

void	print_export(t_minishell *e)
{
	int		i;
	char	**sorted;
	char	*equal_sign;

	sorted = sort_env(e->env);
	if (!sorted)
		return ;
	i = 0;
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", 1);
		equal_sign = ft_strchr(sorted[i], '=');
		if (equal_sign)
		{
			write(1, sorted[i], equal_sign - sorted[i] + 1);
			write(1, "\"", 1);
			ft_putstr_fd(equal_sign + 1, 1);
			write(1, "\"\n", 1);
		}
		else
			ft_putendl_fd(sorted[i], 1);
		i++;
	}
	free_split(sorted);
}