/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newtoken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:02:28 by furizalex         #+#    #+#             */
/*   Updated: 2025/09/01 16:46:03 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token	*ft_newtoken(char *cmd, t_token_type type, int id)
{
	t_token	*head;

	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->id = id;
	head->frag = cmd;
	head->type = type;
	head->open = 0;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}
