/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <anporced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:30:36 by anporced          #+#    #+#             */
/*   Updated: 2024/04/21 15:11:51 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child_here_doc(int *pipe_fds, char **av)
{
	char	*line;

	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp_gnl(line, av[2], ft_strlen(av[2])))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
	}
	close(pipe_fds[1]);
	exit(EXIT_SUCCESS);
}

void	parent_here_doc(int *pipe_fds)
{
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	wait(NULL);
}

void	here_doc(char **av)
{
	int	pipe_fds[2];
	int	pid;

	if (pipe(pipe_fds) == -1)
	{
		perror("Error: Pipe creation for here_doc failed.\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: Fork for here_doc failed.\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_here_doc(pipe_fds, av);
	else
		parent_here_doc(pipe_fds);
}
