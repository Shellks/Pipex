/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:25 by acarlott          #+#    #+#             */
/*   Updated: 2023/04/25 15:57:27 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	get_env(t_pipe *p, char **envp)
{
	int		i;
	char	*get_env;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			get_env = (envp[i] + 5);
	}
	p->env_var = ft_split(get_env, ':');
	if (p->env_var == NULL)
	{
		ft_printf("Split_error\n");
		ft_close(p, 1, 0, 1);
		exit(ERR_SPLIT);
	}
}

int	check_args(t_pipe *p, char **argv)
{
	if (argv[1] == NULL)
	{
		ft_printf("invalid number of arguments\n");
		exit(ERR_ARGS);
	}
	if (ft_strncmp("here_doc", argv[1], 8) == 0 && ft_strlen(argv[1]) < 9)
	{
		p->doc = 1;
		return (5 + p->doc);
	}
	else
	{
		p->doc = 0;
		return (5);
	}
}

void	here_doc(t_pipe *p, char *limiter)
{
	char	*str;

	if (pipe(p->here_doc) < 0)
		exit (ERR_PIPE);
	while (1)
	{
		write(1, "here_doc> ", 11);
		str = get_next_line(STDIN_FILENO);
		if (str == NULL)
			exit (ERR_DOC);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0 && \
		ft_strlen(str) == ft_strlen(limiter) + 1)
		{
			free(str);
			break ;
		}
		write(p->here_doc[1], str, ft_strlen(str));
		free(str);
	}
}

void	pipex_init(t_pipe *p, int argc, char **argv, char **envp)
{
	if (argc < check_args(p, argv))
	{
		ft_printf("invalid number of arguments\n");
		exit(ERR_ARGS);
	}
	p->pipe_num = ((argc - 2));
	if (ft_strncmp("here_doc", argv[1], 8) == 0 && ft_strlen(argv[1]) < 9)
		here_doc(p, argv[2]);
	else
	{
		p->infile = open(argv[1], O_RDONLY);
		if (p->infile < 0)
			ft_printf("no such file or directory: %s\n", argv[1]);
	}
	p->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->outfile < 0)
	{
		ft_printf("no such file or directory: %s\n", argv[argc -1]);
		close(p->infile);
		exit(ERR_OUTFILE);
	}
	get_env(p, envp);
}
