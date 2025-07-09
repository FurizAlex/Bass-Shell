/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:40:34 by alechin           #+#    #+#             */
/*   Updated: 2025/07/09 18:13:21 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	error2exit(char *msg, int status)
{
	ft_printf("%s\n", msg);
	exit(status);
}

int	error4exit(char *msg, int status)
{
	return (ft_printf("%s\n", msg), status);
}

int	error6exit(char *msg, int status)
{
	ft_putstr_fd(msg, status);
	return (status);
}
