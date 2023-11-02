/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:07:48 by acarlott          #+#    #+#             */
/*   Updated: 2023/04/25 19:30:27 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include "../utils/printf/ft_printf.h"

# define ERR_ARGS 1
# define ERR_INFILE 2
# define ERR_OUTFILE 3
# define ERR_ENVP 4
# define ERR_SPLIT 5
# define ERR_PIPE 6
# define ERR_FORK 7
# define ERR_DUP 8
# define ERR_EXEC 9
# define ERR_MALLOC 10
# define ERR_DOC 11
# define ERR_CMD 127
# define CLOSE_FILE 1
# define CLOSE_ALL 2
# define CLOSE_END 3
# define FREE_PARENT 1
# define FREE_CHILD 2

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		pipes[2];
	int		status;
	int		exit_status;
	pid_t	pid;
	char	**env_var;
	char	**cmd_args;
	int		pipe_num;
}	t_pipe;

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
void	ft_free_child(t_pipe *p, int error);
void	ft_free_parent(t_pipe *p, int error);
int		main(int argc, char **argv, char **envp);
void	pipex(t_pipe *p, char **argv, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_close(t_pipe *p, int in_out, int pipe, int std);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	last_child(t_pipe *p, char **envp, char **argv, int i);
void	ft_close_free(t_pipe *p, int close, int free, int error);
void	child_process(t_pipe *p, char **envp, char **argv, int i);
void	pipex_init(t_pipe *pipe, int argc, char **argv, char **envp);

#endif
