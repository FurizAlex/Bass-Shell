/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:31 by alechin           #+#    #+#             */
/*   Updated: 2025/06/30 17:18:54 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	koi_pwd(void)
{
	char	buffer[4096];

	if (!getcwd(buffer, 4096))
		return (error2exit("Fishy Error: couldn't get path", 1), 1);
	printf("%s\n", buffer);
	return (0);
}
