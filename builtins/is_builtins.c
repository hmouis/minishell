/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:50:57 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/24 14:53:30 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return e_echo;
	else if (ft_strcmp(cmd, "cd") == 0)
			return e_cd;
	else if (ft_strcmp(cmd, "pwd") == 0)
			return e_pwd;
	else if (ft_strcmp(cmd, "export") == 0)
			return e_export;
	else if (ft_strcmp(cmd, "unset") == 0)
			return e_unset;
	else if (ft_strcmp(cmd, "env") == 0)
			return e_env;
	else if (ft_strcmp(cmd, "exit") == 0)
			return e_exit;
	return -1;
}

int	exec_builtins(t_env **lst_env, char **cmd, char *filename, int redirect)
{
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stdin = dup(STDIN_FILENO);

	apply_redirect(filename, redirect);

	if (is_builtins(cmd[0]) == e_echo)
		exec_echo(cmd);
	else if (is_builtins(cmd[0]) == e_pwd)
		exec_pwd();
	else if (is_builtins(cmd[0]) == e_export)
		exec_export(lst_env, ++cmd);
	else if (is_builtins(cmd[0]) == e_env)
		exec_env(lst_env);

	// Restore stdout and stdin
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);

	return 0;
}

