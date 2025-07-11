/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:57:04 by rpadasia          #+#    #+#             */
/*   Updated: 2025/07/01 00:46:00 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*get_history_path(void)
{
	char	*home;
	char	*path;
	int		home_len;
	int		total_len;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	home_len = ft_strlen(home);
	total_len = home_len + 20;
	path = malloc(total_len);
	if (!path)
		return (NULL);
	ft_strlcpy(path, home, total_len);
	ft_strlcat(path, "/.minishell_history", total_len);
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
