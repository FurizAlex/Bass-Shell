/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:16:24 by alechin           #+#    #+#             */
/*   Updated: 2025/06/19 10:52:30 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/Wglbx/wglbx.h"

# include "execution.h"
# include "parsing.h"

# define SHELL_NAME "bass shell"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PIPE_LEFT 0
# define PIPE_RIGHT 1

# define SUCCESS 0
# define FAILURE 1

typedef enum e_status
{
	NORMAL,
	QUOTE,
	DOUBLE_QUOTE,
}	t_status;

typedef struct s_minishell
{
	t_env			*env_list;
	t_exec			*cmds;
	struct s_base	*base;
	int				status;
}	t_minishell;

typedef struct s_base
{
	char			**argv;
	int				size;
	int				type;
	int				fd[2];
	struct s_base	*next;
	struct s_base	*prev;
}	t_base;

/* -- Error Handling -- */
int error2exit(char *msg, int status);
int error4exit(char *msg, int status);
int error6exit(char *msg, int status);

#endif