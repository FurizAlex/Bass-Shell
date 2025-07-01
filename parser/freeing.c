/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:00:58 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/30 22:02:00 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*gee i wonder what these are*/
void	free_lexer(t_lexer *lexer)
{
	if (lexer)
	{
		free(lexer->input);
		free(lexer);
	}
}

void	free_ast(t_ast_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->args)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	free(node->filename);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

void	free_parser(t_parser *parser)
{
	if (parser)
		free(parser);
}

void	cleanup_history(void)
{
	save_history_file();
	clear_history();
}