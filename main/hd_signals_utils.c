/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_signals_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:38:33 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/02 22:39:06 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/execution.h"

extern int	g_signal;

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(STDOUT_FILENO, "\n", 1);
		exit(g_signal);
	}
}

void	handle_sigeof_heredoc(int sig)
{
	(void)sig;
	printf("\n");
	g_signal = EXIT_SUCCESS;
	exit(g_signal);
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
