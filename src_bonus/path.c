/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <anporced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:30:21 by anporced          #+#    #+#             */
/*   Updated: 2024/04/21 18:00:12 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	**extract_path(char **env)
{
	int		i;
	char	*env_entr_prefix;
	char	**path;

	i = -1;
	while (env[++i])
	{
		env_entr_prefix = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (ft_strcmp(env_entr_prefix, "PATH") == 0)
		{
			path = ft_split(env[i] + ft_strlen(env_entr_prefix) + 1, ':');
			return (free(env_entr_prefix), path);
		}
		free(env_entr_prefix);
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*each_path;
	char	*exec_path;

	path = extract_path(env);
	if (!path)
		return (perror("Error: PATH environment variable not found.\n"), NULL);
	i = -1;
	while (path[++i])
	{
		each_path = ft_strjoin(path[i], "/");
		exec_path = ft_strjoin(each_path, cmd);
		free(each_path);
		if (access(exec_path, X_OK) == 0)
			return (free_str_array(path), exec_path);
		free(exec_path);
	}
	free_str_array(path);
	return (NULL);
}
