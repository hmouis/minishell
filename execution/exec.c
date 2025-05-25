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
	char *path;

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
	char	*tmp_path = ft_strdup(full_path);
	if (!tmp_path)
		return NULL;
	char *token = ft_strtok(tmp_path, ":");
	while (token)
	{
		int len = str_len(token) + 1 + str_len(file) + 1;
		char *path = malloc(len);
		if (!path)
		{
			ft_putstr_fd("error: malloc failed\n", 2);
			free(tmp_path);
			return NULL;
		}
		ft_strncpy(path, token, str_len(token));
		path[str_len(token)] = '\0';
		ft_strcat(path, "/");
		ft_strcat(path, file);
		if (access(path, X_OK) == 0)
		{
			free(tmp_path);
			return path;
		}
		free(path);
		token = ft_strtok(NULL, ":");
	}
	free(tmp_path);
	return NULL;
}

char	*file_path(char *file)
{
	char	*found;
	char	*path;
	if (file && (file[0] == '/' || ft_strchr(file, '/')))
	{
		if (access(file, X_OK) == 0)
			return ft_strdup(file);
		else
		    return NULL;
	}
	path = get_path();
	if (!path)
		return NULL;
	found = file_location(file, path);
	return found;
}

int	exec_simple_cmd(char **cmd, char *path)
{
	if (!cmd || !*cmd || !path)
		return 0;
	char *file = file_path(path);
	if (!file)
		return 0;
	int child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(file);
		return 0;
	}
	if (child_pid == 0)
	{
		execve(file, cmd, NULL);
		perror("execve");
		return 0;
	}
	else 
	{
		int status;
		waitpid(child_pid, &status, 0);
		free(file);
		return -1;
	}
}
