/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <anporced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:58:16 by anporced          #+#    #+#             */
/*   Updated: 2024/04/21 17:44:24 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_environment_path(char **env)
{
	int		i;
	char	*env_entr_prefix;
	char	**path;

	i = 0;
	while (env[i])
	{
		env_entr_prefix = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (ft_strcmp(env_entr_prefix, "PATH") == 0)
		{
			path = ft_split(env[i] + ft_strlen(env_entr_prefix) + 1, ':');
			return (free(env_entr_prefix), path);
		}
		free(env_entr_prefix);
		i++;
	}
	return (NULL);
}

char	*construct_executable_path(char *command, char **env)
{
	char	**path_dirs;
	char	*path_prefix;
	char	*executable_path;
	int		i;

	i = 0;
	path_dirs = get_environment_path(env);
	if (!path_dirs)
		return (perror("Error: PATH environment variable not found.\n"), NULL);
	while (path_dirs[i])
	{
		path_prefix = ft_strjoin(path_dirs[i], "/");
		executable_path = ft_strjoin(path_prefix, command);
		free(path_prefix);
		if (access(executable_path, X_OK) == 0)
			return (free_array(path_dirs), executable_path);
		free(executable_path);
		i++;
	}
	free_array(path_dirs);
	return (NULL);
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
