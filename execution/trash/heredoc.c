/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:25:49 by alechin           #+#    #+#             */
/*   Updated: 2025/08/26 23:21:29 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	read_heredoc(char *line, int *fd, char *delimiter)
{
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
		close(fd[0]);
	}
}

static bool	heredoc_append(char *cmd, char **original, char *str)
{
	char	*temp;
	char	*start;
	long	length;

	start = str;
	length = ft_strlen(str);
	if (length >= 2 && (str[0] == '"' || str[0] == '\''))
	{
		start = str + 1;
		length -= 2;
	}
	if ((long)ft_strlen(cmd) == length
		&& !ft_strncmp(cmd, start, length))
		return (false);
	temp = *original;
	*original = ft_strjoin(temp, cmd);
	free(temp);
	temp = *original;
	*original = ft_strjoin(temp, "\n");
	free(temp);
	return (true);
}

