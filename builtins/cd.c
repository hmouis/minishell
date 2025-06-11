/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:44:50 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/10 14:23:55 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_cd(t_env **env, t_exec **cmd)
{
	char	*new_dir;
	if (!cmd || !(*cmd) || !env || !(*env))
		return 1;
	(*env)->oldpwd = getcwd(NULL, 0);
	if ((*cmd)->args[1] && (*cmd)->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return 1;
	}
	if (!(*cmd)->args[1])
		new_dir = getenv("HOME");
	else
		new_dir = (*cmd)->args[1];
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_dir , 2);
		perror(":");
		return 1;
	}
	(*env)->pwd = getcwd(NULL, 0);
	update_env(env, (*env)->oldpwd, (*env)->pwd);
	return 0;
}
