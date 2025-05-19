/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:16:24 by alechin           #+#    #+#             */
/*   Updated: 2025/05/19 15:33:11 by alechin          ###   ########.fr       */
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

/*	todo!() -> Data Structures	*/
typedef struct s_minishell
{
	/* data */
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