/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:01 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/20 16:59:39 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/minishell.h"
#include "../includes/execution.h"

void	reset_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	reset_signals_interactive(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_shell_state(void)
{
	t_minishell	*o;

	o = minishell();

	if (g_signal != 0)
	{
		o->last_status = g_signal;
		g_signal = 0;
	}
	reset_signals_interactive();
}
