/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:50:37 by acarlott          #+#    #+#             */
/*   Updated: 2023/04/25 14:18:08 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipe;

	pipex_init(&pipe, argc, argv, envp);
	pipex(&pipe, argv, envp);
	pipe.exit_status = (((pipe.status) & 0xff00) >> 8);
	ft_close_free(&pipe, CLOSE_END, FREE_PARENT, pipe.exit_status);
}
