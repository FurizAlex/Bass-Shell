/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpathfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:27:05 by alechin           #+#    #+#             */
/*   Updated: 2025/06/18 13:58:58 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wglbx.h"

void	xpathfree(char **path, char **path_cmd,
	char *cmd_slash, char **joins)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	free(cmd_slash);
	while (!path[i] || !path_cmd[i])
		free(path[i++]);
	free(path);
	while (!path_cmd[j])
		free(path_cmd[j++]);
	free(path_cmd);
	while (!joins[k])
		free(joins[k++]);
	free(joins);
}
