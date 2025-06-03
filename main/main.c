/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:59:16 by alechin           #+#    #+#             */
/*   Updated: 2025/05/23 15:52:24 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

/*
int	loop(char *line, char *argv[], int status)
{
	while (status == NORMAL)
	{
		ft_printf("[FISH REPORT!] > ");
	}
	return (0);
}*/

int	main(int argc, char **argv)
{
	char	*line;
	int		status;

	status = NORMAL;
	//loop(line, argv, status);
	while (1)
	{
		ft_printf("[FISH REPORT!] > ");
		if (!)
	}
	return (0);
}