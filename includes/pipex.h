/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:28:08 by anporced          #+#    #+#             */
/*   Updated: 2024/04/07 18:45:47 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

// Util functions
void	free_array(char **arr);
char	**get_environment_path(char **env);
char	*construct_executable_path(char *command, char **env);

// Process functions
void	execute_command(char *command, char **env);
void	handle_child_process(int *pipe_fds, char **av, char **env);
void	handle_parent_process(int *pipe_fds, char **av, char **env);

#endif
