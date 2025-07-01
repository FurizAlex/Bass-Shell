/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:59:16 by alechin           #+#    #+#             */
/*   Updated: 2025/06/26 10:25:48 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"
#include "../includes/parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	int		status;

	status = NORMAL;
	while (1)
	{
		cmd = readline("\033[33m-- BASS AMATEUR SHELL --
			\033[36m\n[🐡 FISH BITES] o->\033[0m ");
	}
	return (0);
}
