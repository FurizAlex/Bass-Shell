/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: furizalex <furizalex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:41:40 by alechin           #+#    #+#             */
/*   Updated: 2025/08/17 23:08:55 by furizalex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

static int	count_cmds(t_root *node)
{
	if (!node)
		return (0);
	if (!node->left && !node->right)
		return (1);
	return (count_cmds(node->left) + count_cmds(node->right));
}

static t_root	*nth_leaf(t_root *node, int *k)
{
	t_root	*res;

	if (!node)
		return (NULL);
	if (!node->left && !node->right)
	{
		if (*k == 0)
			return (node);
		*k -= 1;
		return (NULL);
	}
	res = nth_leaf(node->left, k);
	if (res)
		return (res);
	return (nth_leaf(node->right, k));
}

static t_root	*get_nth_cmd(t_root *root, int idx)
{
	int	k;

	k = idx;
	return (nth_leaf(root, &k));
}

static int	make_pipes(int **pfds, int n)
{
	int	i;
	int	total;

	*pfds = NULL;
	if (n <= 1)
		return (0);
	total = (n - 1) * 2;
	*pfds = malloc(sizeof(int) * total);
	if (!*pfds)
		return (error2exit("Fishy Error: Couldn't allocate pipe array", 1), -1);
	i = 0;
	while (i < n - 1)
	{
		if (pipe(*pfds + (i * 2)) < 0)
		{
			free(*pfds);
			*pfds = NULL;
			return (error2exit("Fishy Error: Couldn't get pipe", 1), -1);
		}
		i++;
	}
	return (total);
}

static void	close_all(int *pfds, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		close(pfds[i]);
		i++;
	}
}

int	pipex(t_root *root)
{
	int		n;
	int		total;
	int		*pfds;
	int		i;
	pid_t	pid;
	int		status;
	int		last;
	t_root	*cmd;

	n = count_cmds(root);
	if (n <= 0)
		return (error2exit("Fishy Error: No commands to run", 1), 1);
	total = make_pipes(&pfds, n);
	if (total < 0)
		return (1);
	i = 0;
	last = 0;
	while (i < n)
	{
		/* parent: announce fork about to happen */
		ft_printf("DBG: pipex parent about to fork child index=%d n=%d\n", i, n);
		pid = fork();
		if (pid < 0)
		{
			if (pfds)
				free(pfds);
			return (error2exit("Fishy Error: fork", 1), 1);
		}
		if (pid == 0)
		{
			int	child_status;

			/* child: wire pipes */
			if (i > 0)
			{
				if (dup2(pfds[(i - 1) * 2], STDIN_FILENO) < 0)
					_exit(1);
			}
			if (i < n - 1)
			{
				if (dup2(pfds[i * 2 + 1], STDOUT_FILENO) < 0)
					_exit(1);
			}
			if (pfds)
				close_all(pfds, total);
			/* now obtain the subtree for this command index */
			cmd = get_nth_cmd(root, i);
			/* debug: show which subtree token id the child will run */
			ft_printf("DBG: pipex child idx=%d pid=%d cmd_head_id=%d\n",
				i, getpid(), cmd && cmd->tokens && cmd->tokens[0]
				? cmd->tokens[0]->id : -1);
			/* apply redirections and run the command subtree in this process */
			child_status = redirect_prompt(cmd);
			_exit(child_status);
		}
		i++;
	}
	/* parent: close and free pipes, then wait */
	if (pfds)
	{
		close_all(pfds, total);
		free(pfds);
	}
	ft_printf("DBG: pipex parent closed all fds, waiting for children\n");
	i = 0;
	while (i < n)
	{
		wait(&status);
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
		i++;
	}
	return (last);
}