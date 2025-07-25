/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:59:16 by alechin           #+#    #+#             */
/*   Updated: 2025/07/25 21:33:38 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"
#include "../includes/parsing.h"

int	main(int argc, char **argv, char **env)
{
	char		*cmd;
	t_minishell	o;

	(void)argc;
	(void)argv;
	(void)cmd;
	(void)env;
	initialise(&argc, &argv, &o.token, env);
	setup_signals();
	setup_history();
	shell_loop();
	cleanup_history();
	return (0);
}
