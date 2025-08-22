/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:09:03 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/22 16:55:04 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int g_signal = 0;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigeof(int sig)
{
	(void)sig;
	printf("exit\n");
	g_signal = EXIT_SUCCESS;
	exit(g_signal);
}

bool	handle_eof_input(char *cmd)
{
	if (!cmd)
	{
		write(1, "exit\n", 5);
		return (true);
	}
	return (false);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	process_signal_state(t_minishell *msh)
{
	if (g_signal != 0)
	{
		msh->last_status = g_signal;
		g_signal = 0;
	}
}
