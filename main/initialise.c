/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:16:55 by alechin           #+#    #+#             */
/*   Updated: 2025/07/11 16:41:44 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	initialise(int *argc, char ***argv, t_minishell *o, char ***env)
{
	(void)argc;
	(void)argv;
	(void)env;
	o->status = 0;
	o->lcl_env = 0;
	o->env = NULL;
	o->export = NULL;
	o->root = NULL;
}
