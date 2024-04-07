/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:44:57 by anporced          #+#    #+#             */
/*   Updated: 2024/04/07 18:45:21 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	validate_args_count(int ac, int is_here_doc)
{
	if ((is_here_doc && ac < 6) || (!is_here_doc && ac < 5))
	{
		perror("Error: Incorrect number of arguments.\n");
		exit(EXIT_FAILURE);
	}
}

int	open_file(char *filename, int mode)
{
	int	permissions;
	int	fd;

	if (mode == (O_WRONLY | O_CREAT | O_APPEND))
		permissions = 0644;
	else
		permissions = 0777;
	fd = open(filename, mode, permissions);
	if (fd == -1)
	{
		perror("Error: File opening failed.\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	free_str_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
