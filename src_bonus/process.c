/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:31:45 by anporced          #+#    #+#             */
/*   Updated: 2024/04/07 18:51:43 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	handle_child_process(int *pfd, char *cmd, char **env)
{
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	execute_command(cmd, env);
}

void	handle_parent_process(int *pipe_fds)
{
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	wait(NULL);
}
