/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:19:08 by acarlott          #+#    #+#             */
/*   Updated: 2023/04/25 14:19:11 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	pipex_init(t_pipe *p, int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_printf("invalid number of arguments\n");
		exit(ERR_ARGS);
	}
	p->pipe_num = ((argc - 2));
	p->infile = open(argv[1], O_RDONLY);
	if (p->infile < 0)
		ft_printf("no such file or directory: %s\n", argv[1]);
	p->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->outfile < 0)
	{
		ft_printf("no such file or directory: %s\n", argv[argc -1]);
		close(p->infile);
		exit(ERR_OUTFILE);
	}
	get_env(p, envp);
}
