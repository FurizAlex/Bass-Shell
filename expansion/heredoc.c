/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:25:49 by alechin           #+#    #+#             */
/*   Updated: 2025/06/26 14:51:47 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	read_heredoc(char *line, int fd, char *delimiter)
{
	char	*doc;
	int		i;

	i = 0;
	doc = ft_strdup("");
	if (!line)
		error2exit("🍥 Fishy Error: No line in heredoc\n", 1);
	while (1)
	{
		line = readline("o-> ");
		if (!line)
			error2exit("🍥 Fishy Warning: Heredoc delimited by EOF\n", 2);
		if (!line || !comp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		dup2(fd[0], 0);
		close(fd[0], 0);
	}
}
