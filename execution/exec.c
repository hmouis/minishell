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

static void	msg_no_such_file(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

static void	msg_error(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '/')
		msg_no_such_file(arg);
	else if (arg[0] == '.' && arg[1] == '/')
	{
		if (access(arg, F_OK) == 0 && access(arg, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
		msg_no_such_file(arg);
	}
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	*is_there_path(t_env *list)
{
	t_env	*tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}

int	exec_cmd(char **env, t_exec **cmd, t_env *lst_env)
{
	char	*file;
	struct stat	sb;

	if (!cmd || !*cmd || !(*cmd)->args || !(*cmd)->args[0])
		exit(127);
	if (!is_there_path(lst_env) && ((*cmd)->args[0][0] != '/'))
		msg_no_such_file((*cmd)->args[0]);
	file = file_path((*cmd)->args[0]);
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