/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:16:55 by alechin           #+#    #+#             */
/*   Updated: 2025/07/25 22:57:03 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	initialise(int *argc, char ***argv, t_token **tokens, char **env)
{
	t_minishell	*o;

	(void)argc;
	(void)argv;
	(void)env;
	*tokens = NULL;
	o = minishell();
	o->lcl_env = 0;
	o->last_status = 0;
	o->env = cpyenv(env);
	o->export = ft_calloc(countword(o->env) + 1, sizeof(int));
	o->token = NULL;
	o->root = NULL;
	o->status = UNDECLARED;
}
