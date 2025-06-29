/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:24:06 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/29 17:24:13 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
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

char	*file_path(char *file)
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
	path = get_path();
	if (!path)
		return (NULL);
	found = file_location(file, path);
	return (found);
}
