/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:28:17 by alechin           #+#    #+#             */
/*   Updated: 2025/07/09 18:14:14 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(void)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("\033[33m-- BASS AMATEUR SHELL --\033[36m\n[🐡 FISH BITES] o->\033[0m ");
		if (!cmd)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!is_empty_input(cmd))
		{
			add_history(cmd);
			//process_input(cmd);
		}
		free(cmd);
	}
}
