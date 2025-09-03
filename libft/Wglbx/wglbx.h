/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wglbx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:00:32 by alechin           #+#    #+#             */
/*   Updated: 2025/07/10 12:32:30 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WGLBX_H
# define WGLBX_H

# include "../../includes/minishell.h"

typedef struct s_minishell	t_minishell;

char	*getxenv(char *envp, t_minishell *e);
int		comp(const char *s1, const char *s2);
int		ncomp(const char *s1, const char *s2, size_t n);
int		measure(const char *str);
int		sdigit(char *str);
int		valid_env_ch(char c);
int		countword(char **wgstr_of_array);
void	array2clear(char **argv);
void	xpathfree(char **path, char **path_cmd,
			char *cmd_slash, char **joins);
char	**cpyenv(char **env);
char	*dupnxtra(char *str, size_t n);

#endif