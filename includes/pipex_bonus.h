/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:27:34 by anporced          #+#    #+#             */
/*   Updated: 2024/04/07 18:51:43 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
void	free_str_array(char **arr);
char	**extract_path(char **env);
char	*get_path(char *cmd, char **env);

// Process functions
void	execute_command(char *cmd, char **env);
void	create_pipes(char *cmd, char **env);
void	launch_processes(int ac, char **av, char **env);
void	handle_child_process(int *pfd, char *cmd, char **env);
void	handle_parent_process(int *pipe_fds);
void	child_here_doc(int *pipe_fds, char **av);
void	parent_here_doc(int *pipe_fds);
void	here_doc(char **av);

// Validation and file handling
void	validate_args_count(int ac, int is_here_doc);
int		open_file(char *filename, int mode);

#endif
