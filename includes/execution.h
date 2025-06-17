/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:33:54 by alechin           #+#    #+#             */
/*   Updated: 2025/06/17 13:03:29 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef enum e_redir_t
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_t;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	t_redir_t		type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	char			**argv;
	char			*cmd_path;
	int				infile;
	int				outfile;
	bool			has_pipe;
	bool			is_builtin;
	t_redir			*redirs;
	struct s_exec	*next;
}	t_exec;

#endif