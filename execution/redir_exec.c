/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:56 by alechin           #+#    #+#             */
/*   Updated: 2025/06/18 15:18:53 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int redir_type(int type)
{
	return (type == TOKEN_REDIRECT_IN
		|| TOKEN_REDIRECT_OUT
		|| TOKEN_REDIRECT_APPEND
		|| TOKEN_HEREDOC);
}

