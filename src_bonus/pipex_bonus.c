/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:44:54 by anporced          #+#    #+#             */
/*   Updated: 2024/04/16 19:31:43 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	execute_command(char *cmd, char **env)
{
	char	**av;
	char	*path;

	av = ft_split(cmd, ' ');
	if (!av)
	{
		perror("Error: Command splitting failed.\n");
		exit(EXIT_FAILURE);
	}
	path = get_path(av[0], env);
	if (!path)
	{
		free_str_array(av);
		perror("Error: Executable path not found.\n");
		exit(EXIT_FAILURE);
	}
	if (execve(path, av, env) == -1)
	{
		perror("Error: Command execution failed.\n");
		free_str_array(av);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	create_pipes(char *cmd, char **env)
{
	int	pipe_fds[2];
	int	pid;

	if (pipe(pipe_fds) == -1)
	{
		perror("Error: Pipe creation failed.\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: Fork failed.\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		handle_child_process(pipe_fds, cmd, env);
	else
		handle_parent_process(pipe_fds);
}

void	launch_processes(int ac, char **av, char **env)
{
	int	fd;
	int	i;

	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		fd = open_file(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND);
		here_doc(av);
		i = 3;
	}
	else
	{
		fd = open_file(av[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		i = 2;
		fd = open_file(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
	}
	while (i < ac - 2)
		create_pipes(av[i++], env);
	dup2(fd, STDOUT_FILENO);
	execute_command(av[ac - 2], env);
	close(fd);
}

int	main(int ac, char **av, char **env)
{
	int	is_here_doc;

	if (ft_strcmp(av[1], "here_doc") == 0)
		is_here_doc = 1;
	else
		is_here_doc = 0;
	validate_args_count(ac, is_here_doc);
	launch_processes(ac, av, env);
	return (0);
}
