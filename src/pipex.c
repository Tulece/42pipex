/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <anporced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:42:00 by anporced          #+#    #+#             */
/*   Updated: 2024/04/21 15:19:50 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_command(char *command, char **env)
{
	char	**av;
	char	*path;

	av = ft_split(command, ' ');
	if (!av)
	{
		perror("Error: Command parsing failed.\n");
		exit(EXIT_FAILURE);
	}
	path = construct_executable_path(av[0], env);
	if (!path)
	{
		free_array(av);
		perror("Error: Executable path not found.\n");
		exit(EXIT_FAILURE);
	}
	if (execve(path, av, env) == -1)
	{
		perror("Error: Command execution failed.\n");
		free_array(av);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	handle_child_process(int *pipe_fds, char **av, char **env)
{
	int	fd;

	close(pipe_fds[0]);
	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("Error: File opening failed.\n");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	execute_command(av[2], env);
	close(fd);
}

void	handle_parent_process(int *pipe_fds, char **argv, char **env)
{
	int	fd;

	close(pipe_fds[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error: File opening/creating failed.\n");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	execute_command(argv[3], env);
	close(fd);
	wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	int	pipe_fds[2];
	int	pid;

	if (ac != 5)
		return (ft_printf("Error: Incorrect number of arguments.\n"), 1);
	if (pipe(pipe_fds) == -1)
		return (perror("Error: Pipe creation failed.\n"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("Error: Fork failed.\n"), 1);
	if (pid == 0)
		handle_child_process(pipe_fds, av, env);
	else
		handle_parent_process(pipe_fds, av, env);
	return (0);
}
