/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:59:16 by alechin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/17 13:24:53 by alechin          ###   ########.fr       */
=======
/*   Updated: 2025/06/17 13:31:19 by alechin          ###   ########.fr       */
>>>>>>> 77b7b4fc6c7d044e0b6ac7348963356f383df25e
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
		cmd = readline("\033[33m-- BASS AMATEUR SHELL --\033[36m\n[🐡 FISH BITES] o->\033[0m ");
	}
	return (0);
}