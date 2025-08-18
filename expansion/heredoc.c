/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:25:49 by alechin           #+#    #+#             */
/*   Updated: 2025/08/16 21:03:14 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	read_heredoc(char *line_unused, int *fd, char *delimiter)
{
	char	*line;

	(void)line_unused;
	while (1)
	{
		line = readline("o-> ");
		if (!line)
		{
			ft_putstr_fd("Fishy Warning: Heredoc delimited by EOF\n", 2);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
}

int	heredoc_checker(t_root **root)
{
	if ((*root)->tokens && (*root)->tokens[0]->type == TOKEN_HEREDOC)
	{
		if (!(*root)->tokens[1] || (*root)->tokens[1]->type != TOKEN_WORD)
			return (error2exit("Fishy Error: Heredoc requires a delimiter", 1), 1);
	}
	return (UNDECLARED);
}
