/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:39:12 by acarlott          #+#    #+#             */
/*   Updated: 2023/04/25 14:40:05 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	last_process(t_pipe *p, char **envp, char **argv, int i)
{	
	if (pipe(p->pipes) == -1)
		ft_close_free(p, CLOSE_FILE, FREE_PARENT, ERR_PIPE);
	p->pid = fork ();
	if (p->pid == -1)
		ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_FORK);
	if (p->pid == 0)
		last_child(p, envp, argv, i);
	else
	{
		close(p->pipes[0]);
		close(p->pipes[1]);
	}
}

static void	parent_process(t_pipe *p, char **envp, char **argv, int i)
{	
	if (pipe(p->pipes) == -1)
		ft_close_free(p, CLOSE_FILE, FREE_PARENT, ERR_PIPE);
	p->pid = fork ();
	if (p->pid == -1)
		ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_FORK);
	if (p->pid == 0)
	{
		if (i == 2 && access(argv[1], R_OK))
			ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_INFILE);
		child_process(p, envp, argv, i);
	}
	else
	{
		close(p->pipes[1]);
		if (dup2(p->pipes[0], 0) < 0)
		{
			close(p->pipes[0]);
			ft_close(p, 1, 0, 1);
			ft_free_parent(p, ERR_DUP);
		}
		close(p->pipes[0]);
	}
}

void	pipex(t_pipe *p, char **argv, char **envp)
{
	int	wait_all;
	int	i;

	wait_all = 0;
	dup2(p->infile, 0);
	i = 1;
	while (++i < p->pipe_num)
		parent_process(p, envp, argv, i);
	last_process(p, envp, argv, i);
	waitpid(p->pid, &p->status, 0);
	close(STDIN_FILENO);
	while (wait_all != -1)
		wait_all = waitpid(-1, NULL, 0);
}
