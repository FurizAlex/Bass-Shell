/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:39:06 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/02 22:59:13 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <execution.h>
#include <parsing.h>

#define REDIRECT_IN     0
#define REDIRECT_OUT    1
#define REDIRECT_APPEND 2
#define REDIRECT_HEREDOC 3

int	apply_redirect_heredoc(char *filename, int *saved_fd)
{
	if (apply_heredoc(filename, saved_fd) != 0)
	{
		free(filename);
		return (1);
	}
	return (0);
}
