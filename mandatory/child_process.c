/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:21:44 by acarlott          #+#    #+#             */
/*   Updated: 2023/04/25 14:04:34 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_cmd(t_pipe *p, char *cmd)
{
	char	*temp;
	char	*cmd2;
	int		i;

	i = 0;
	if (access(cmd, 0) == 0)
		return (cmd);
	if (cmd[0] == '/')
		return (NULL);
	while (p->env_var[i])
	{
		temp = ft_strjoin(p->env_var[i], "/");
		cmd2 = ft_strjoin(temp, cmd);
		free (temp);
		if (access(cmd2, X_OK) == 0)
			return (cmd2);
		free (cmd2);
		i++;
	}
	return (NULL);
}

void	last_child(t_pipe *p, char **envp, char **argv, int i)
{
	char	*cmd2;

	close(p->pipes[0]);
	if (dup2(p->outfile, 1) < 0)
		ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_DUP);
	p->cmd_args = ft_split(argv[i], ' ');
	if (p->cmd_args == NULL)
		ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_SPLIT);
	cmd2 = get_cmd(p, p->cmd_args[0]);
	if (cmd2 == NULL)
	{
		ft_printf("command not found: %s\n", argv[i]);
		close(p->pipes[1]);
		ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_CMD);
	}
	execve(cmd2, p->cmd_args, envp);
	close(p->pipes[1]);
	ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_EXEC);
}

void	child_process(t_pipe *p, char **envp, char **argv, int i)
{
	char	*cmd2;

	close(p->pipes[0]);
	if (dup2(p->pipes[1], 1) < 0)
		ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_DUP);
	p->cmd_args = ft_split(argv[i], ' ');
	if (p->cmd_args == NULL)
		ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_SPLIT);
	cmd2 = get_cmd(p, p->cmd_args[0]);
	if (cmd2 == NULL)
	{
		ft_printf("command not found: %s\n", argv[i]);
		close(p->pipes[1]);
		ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_CMD);
	}
	execve(cmd2, p->cmd_args, envp);
	close(p->pipes[1]);
	ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_EXEC);
}
