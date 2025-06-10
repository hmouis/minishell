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
		char *path = ft_malloc(len, 1);
		if (!path)
		{
			ft_putstr_fd("error: malloc failed\n", 2);
			return NULL;
		}
		ft_strncpy(path, token, str_len(token));
		path[str_len(token)] = '\0';
		ft_strcat(path, "/");
		ft_strcat(path, file);
		if (access(path, X_OK) == 0)
			return path;
		token = ft_strtok(NULL, ":");
	}
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

int	exec_cmd(char **env, t_exec **cmd, t_final_struct *struc)
{
	int	status;
	if (!cmd || !*cmd || !(*cmd)->args || !(*cmd)->args[0])
		exit(127);
	char	*path = struc->args->str;
	char *file = file_path(path);
	if (!file)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd((*cmd)->args[0], 2);
		ft_putstr_fd("\n", 2);
		status = 127;
		(*cmd)->exit_status = &status;
		ft_malloc(0, 0);
		exit(127);
	}
    	execve(file, (*cmd)->args, env);
    	perror("execve");
	status = 126;
	(*cmd)->exit_status = &status;
	exit(126);
}
