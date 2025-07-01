/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:27:14 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/29 21:51:40 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	update_quote_state(char c, bool *in_s, bool *in_d)
{
	if (c == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (c == '"' && !(*in_s))
		*in_d = !(*in_d);
}

static bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static bool	should_skip_char(char c, bool in_s, bool in_d)
{
	if (c == '\'' && !in_d)
		return (true);
	if (c == '"' && !in_s)
		return (true);
	return (false);
}

/*My quote removal macro/engine:
strips quote characters while preserving content and tracking quote state*/
char	*process_word_content(char *raw)
{
	char	*processed;
	int		i;
	int		len;
	bool	s;
	bool	d;

	processed = malloc(1024);
	i = 0;
	len = 0;
	s = false;
	d = false;
	while (raw[i])
	{
		if (is_quote(raw[i]))
			update_quote_state(raw[i], &s, &d);
		if (!should_skip_char(raw[i], s, d))
			processed[len++] = raw[i];
		i++;
	}
	processed[len] = '\0';
	return (processed);
}