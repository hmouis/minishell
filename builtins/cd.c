/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:03:31 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:28:01 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static void	cd_error_msg(char *new_dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(new_dir, 2);
	perror(":");
	g_exit_status = 1;
}

static void	msg_too_many_arguments(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	g_exit_status = 1;
}

static void	initialize_pwd_tmp(t_env **env, char **tmp)
{
	(*env)->pwd = getcwd(NULL, 0);
	*tmp = NULL;
	*tmp = ft_strdup((*env)->pwd);
	free((*env)->pwd);
	(*env)->pwd = NULL;
	(*env)->pwd = ft_strdup(*tmp);
}

void	exec_cd(t_env **env, t_exec **cmd)
{
	char	*new_dir;
	char	*tmp;

	if (!cmd || !(*cmd) || !env || !(*env))
		return ;
	(*env)->oldpwd = getcwd(NULL, 0);
	tmp = NULL;
	tmp = ft_strdup((*env)->oldpwd);
	free((*env)->oldpwd);
	(*env)->oldpwd = NULL;
	(*env)->oldpwd = ft_strdup(tmp);
	if ((*cmd)->args[1] && (*cmd)->args[2])
		return (msg_too_many_arguments());
	if (!(*cmd)->args[1])
		new_dir = getenv("HOME");
	else
		new_dir = (*cmd)->args[1];
	if (chdir(new_dir) == -1)
		return (cd_error_msg(new_dir));
	initialize_pwd_tmp(env, &tmp);
	update_env(env, (*env)->oldpwd, (*env)->pwd);
	g_exit_status = 0;
}
