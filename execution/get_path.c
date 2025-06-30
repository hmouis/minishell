/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:24:06 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:30:07 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/expansions.h"
#include "../includes/gc.h"

char	*get_path(t_env *env)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			path = env->data;
		env = env->next;
	}
	return (path);
}

static char	*file_location(char *file, char *full_path)
{
	char	*tmp_path;
	char	*token;
	int		len;
	char	*path;

	tmp_path = ft_strdup(full_path);
	if (!tmp_path)
		return (NULL);
	token = ft_strtok(tmp_path, ":");
	while (token)
	{
		len = str_len(token) + 1 + str_len(file) + 1;
		path = ft_malloc(len, 1);
		if (!path)
			return (NULL);
		ft_strncpy(path, token, str_len(token));
		path[str_len(token)] = '\0';
		ft_strcat(path, "/");
		ft_strcat(path, file);
		if (access(path, X_OK) == 0)
			return (path);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*file_path(t_env *env, char *file)
{
	char	*found;
	char	*path;

	if (!file || !file[0])
		return (NULL);
	if (file && (file[0] == '/' || ft_strchr(file, '/')))
	{
		if (access(file, X_OK) == 0)
			return (ft_strdup(file));
		else
			return (NULL);
	}
	path = get_path(env);
	if (!path)
		return (NULL);
	found = file_location(file, path);
	return (found);
}
