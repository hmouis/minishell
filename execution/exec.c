/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:49:04 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/19 16:49:28 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path()
{
	char	*path;

	path = getenv("PATH");
	if (!path)
	{
		perror("getenv");
		return NULL;
	}
	return path;
}

char	*file_location(char *file, char *full_path)
{
	struct stat	file_inf;
	char		*tmp_path;
	char		*path;
	char		*token;

	tmp_path = ft_strdup(full_path);
	token = ft_strtok(tmp_path, ":");
	while (token)
	{
		path = malloc(str_len(token) + 1 + str_len(file) + 1);
		if (!path)
		{
			ft_putstr_fd("error: malloc failed\n", 2);
			free(tmp_path);
			return NULL;
		}
		ft_strncpy(path, token, str_len(token));
		ft_strcat(path, "/");
		ft_strcat(path, file);
		if (access(path, X_OK) == 0)
		{
			free(tmp_path);
			return path;
		}
		free(path);
		path = NULL;
		token = ft_strtok(NULL, ":");
	}
	free(tmp_path);
	return NULL;
}

char	*file_path(char *file)
{
	if (file != NULL || file[0] == '/')
	{
		if (access(file, X_OK) == 0)
			return file;
		else
		{
			return NULL;
		}
	}
	return NULL;
}

