/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:25:24 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/27 18:48:57 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
	{
		return (NULL);
	}
	return (path);
}

char	*file_location(char *file, char *full_path)
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

static void	msg_error(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 127;
		exit(127);
	}
	else if (arg[0] == '.' && arg[1] == '/')
	{
		if (access(arg, F_OK) == 0 && access(arg, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			g_exit_status = 126;
			exit(126);
		}
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 127;
		exit(127);
	}	
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

/*char	*is_there_path(t_env *list)*/
/*{*/
/*	if (!list)*/
/*		return NULL;*/
/*	t_env	*tmp;*/
/**/
/*	tmp = list;*/
/*	while (tmp)*/
/*	{*/
/*		if (ft_strcmp(tmp->key, "PATH") == 0)*/
/*			return tmp->data;*/
/*		tmp = tmp->next;*/
/*	}*/
/*	return NULL;*/
/*}*/

int	exec_cmd(char **env, t_exec **cmd, t_final_struct *struc)
{
	char	*file;
	struct stat sb;

	if (!cmd || !*cmd || !(*cmd)->args || !(*cmd)->args[0])
		exit(127);
	if (is_builtins((*cmd)->args[0]) != -1)
	{
		exec_builtins(&(struc->lst_env), cmd, struc);
		exit(g_exit_status);
	}
	file = file_path((*cmd)->args[0]);
	/*if (!is_there_path(struc->lst_env))*/
	/*{*/
	/*	ft_putstr_fd("minishell: ", 2);*/
	/*	ft_putstr_fd((*cmd)->args[0], 2);*/
	/*	ft_putstr_fd(": No such file or directory\n", 2);*/
	/*	exit(127);*/
	/**/
	/*}*/
	if (stat(file, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (!file || file[str_len(file) - 1] == '/')
	{
		msg_error((*cmd)->args[0]);
		ft_malloc(0, 0);
		exit(127);
	}
	execve(file, (*cmd)->args, env);
	exit(126);
}
