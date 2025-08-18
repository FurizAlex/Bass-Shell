/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:28:17 by alechin           #+#    #+#             */
/*   Updated: 2025/08/17 23:11:53 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "execution.h"
#include "parsing.h"

void	debug_print_full_tokens(t_token *head)
{
	t_token	*cur;

	if (!head)
	{
		ft_putstr_fd("DBG TOKENS: head == NULL\n", 2);
		return ;
	}
	cur = head;
	ft_putstr_fd("DBG TOKENS: start dump\n", 2);
	while (cur)
	{
		ft_printf("TOK id=%d type=%d value='%s' is_open=%d addr=%p prev=%p next=%p lexer=%p\n",
			cur->id,
			(int)cur->type,
			(cur->value ? cur->value : "(null)"),
			(int)cur->is_open,
			(void *)cur,
			(void *)cur->prev,
			(void *)cur->next,
			(void *)cur->lexer);
		/* also print lexer internal flags if available */
		if (cur->lexer)
		{
			ft_printf("    LEX pos=%d in_s=%d in_d=%d input_addr=%p\n",
				cur->lexer->pos,
				(int)cur->lexer->in_single_quote,
				(int)cur->lexer->in_double_quote,
				(void *)cur->lexer->input);
		}
		if (cur->type == TOKEN_EOF)
			break ;
		cur = cur->next;
	}
	ft_putstr_fd("DBG TOKENS: end dump\n", 2);
}

static int	count_words(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type != TOKEN_WORD)
			break ;
		count++;
		head = head->next;
	}
	return (count);
}

static char	**build_argv_from_tokens_and_expand(t_token *head,
			int count, t_minishell *o)
{
	char	**argv;
	int		i;
	char	*expanded;
	t_root	tmp_root;

	argv = malloc((count + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	tmp_root.msh = o;
	while (i < count && head)
	{
		/* first, expand variables and remove quotes using your expand helpers */
		expanded = expand_string(head->value, &tmp_root);
		if (!expanded)
			argv[i] = ft_strdup("");
		else
		{
			argv[i] = remove_quotes(expanded);
			free(expanded);
		}
		if (!argv[i])
		{
			while (--i >= 0)
				free(argv[i]);
			free(argv);
			return (NULL);
		}
		i++;
		head = head->next;
	}
	argv[i] = NULL;
	return (argv);
}

static int	exec_argv_with_env_and_wait(char **argv, char **env)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!argv || !argv[0])
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		path = exec_path(argv[0], env);
		if (path)
		{
			execve(path, argv, env);
			perror(path);
			free(path);
		}
		else
		{
			execve(argv[0], argv, env);
			perror(argv[0]);
		}
		_exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

static void	attach_exec(t_root **root, t_token **tokens)
{
	t_minishell	*o;
	t_micro		shell;
	t_token		*temp;
	int			first_id;
	int			last_id;

	o = minishell();
	*root = NULL;
	ft_printf("DBG: attach_exec start tokens_head_id=%d\n", (*tokens)->id);
	first_id = (*tokens)->id;
	last_id = ft_tokenlst(*tokens)->id;
	if (first_id <= last_id)
	{
		shell.id_start = first_id;
		shell.id_end = last_id;
	}
	else
	{
		shell.id_start = last_id;
		shell.id_end = first_id;
	}
	shell.length = 0;
	temp = *tokens;
	while (temp)
	{
		shell.length++;
		temp = temp->next;
	}
	*root = create_initial_root(tokens, &shell);
	o->root = *root;
	if (!(*root))
	{
		int		count;
		char	**argv;
		int		ret;
	
		count = count_words(*tokens);
		ft_printf("DBG: attach_exec - create_initial_root returned NULL, fallback_word_count=%d\n", count);
		if (count > 0)
		{
			argv = build_argv_from_tokens_and_expand(*tokens, count, o);
			if (argv)
			{
				ret = exec_argv_with_env_and_wait(argv, o->env);
				/* use your array free helper: array2clear or similar */
				array2clear(argv);
				o->last_status = (ret >= 0) ? ret : 127;
			}
			else
				o->last_status = 127;
		}
		else
		{
			ft_putstr_fd("attach_exec: could not create root\n", 2);
			o->status = UNDECLARED;
			o->last_status = 1;
		}
		return ;
	}
	(*root)->msh = o;
	o->status = recursive_tree(root, shell, tokens, true);
	if (o->status == UNDECLARED)
	{
		if (o->root)
			o->last_status = execution(*root);
		else
			o->last_status = 1;
	}
	terminate_ast(root);
}

static void	status_clearance(void)
{
	t_minishell	*o;
	t_root		*root;

	o = minishell();
	if (o->status == UNDECLARED)
		attach_exec(&root, &o->token);
	if (o->status == INTERACTIVE)
		o->last_status = 130;
	if (o->status == EOFS)
		return ;
}

static bool	is_empty_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	process_input(char *input)
{
	t_token		*tokens;
	t_ast_node	*ast;
	t_minishell	*o;

	o = minishell();
	tokens = tokenize(input);
	if (!tokens)
		return ;
	set_token_prev_pointers(tokens);
	debug_print_full_tokens(tokens);
	o->token = tokens;
	ast = parse(tokens);
	o->status = UNDECLARED;
	status_clearance();
	if (ast)
		free_ast(ast);
}

void	shell_loop(void)
{
	char		*cmd;

	while (1)
	{
		cmd = readline("\033[33m-- BASS AMATEUR SHELL --\033[36m\n[🐡 FISH BITES] o->\033[0m ");
		printf("Input received: '%s'\n", cmd);
		if (!cmd)
		{
			write(1, "Exit\n", 5);
			break ;
		}
		if (!is_empty_input(cmd))
		{
			add_history(cmd);
			process_input(cmd);
		}
		free(cmd);
	}
}
