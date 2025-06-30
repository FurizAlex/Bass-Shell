/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:57:04 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/30 22:03:27 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*get_history_path(void)
{
	char	*home;
	char	*path;
	int		home_len;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	home_len = ft_strlen(home);
	path = malloc(home_len + 20);
	if (!path)
		return (NULL);
	ft_strcpy(path, home);
	ft_strcat(path, "/.minishell_history");
	return (path);
}

void	load_history_file(void)
{
	char	*history_path;

	history_path = get_history_path();
	if (history_path)
	{
		read_history(history_path);
		free(history_path);
	}
}

void	save_history_file(void)
{
	char	*history_path;

	history_path = get_history_path();
	if (history_path)
	{
		write_history(history_path);
		free(history_path);
	}
}

void	setup_history(void)
{
	using_history();
	stifle_history(1000);
	load_history_file();
}
