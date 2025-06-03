/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:16:24 by alechin           #+#    #+#             */
/*   Updated: 2025/05/23 14:56:47 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

# define STDIN 0
# define STDOUT 1
# define STDDER 2

# define MAX_COMMAND_LINE 1024

/*	todo!() -> Data Structures	*/
typedef enum e_status
{
	NORMAL,
}	t_status

typedef struct s_minishell
{
	struct s_base *base;
	struct s_pipe *pipe;
}	t_minishell;

typedef struct	s_base
{
	char			**argv;
	int				size;
	int				type;
	int				fd[2];
	struct s_base	*next;
	struct s_base	*prev;
}	t_base;

typedef struct s_pipe
{
	/* todo!() */
}	t_pipe;

#endif