/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 04:43:48 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/17 12:26:57 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void child_process(t_final_struct *fnl,int in_fd, int out_fd, t_env *lst_env, char **env, t_exec **exec)
{
	int	status;
	if (!fnl || !lst_env || !exec)
		exit(EXIT_FAILURE);
	apply_redirect(fnl);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	exec_cmd(env, exec, fnl);
}

void	execute(t_final_struct *list, t_env *lst_env, char **env)
{
	int fd[2];
	int in_fd = STDIN_FILENO;
	int status;
	pid_t pid;
	t_exec *exec;
	t_final_struct *cmd = list;

	if (cmd && !cmd->next && cmd->args && is_builtins(cmd->args->str) != -1)
	{
		int saved_in = dup(STDIN_FILENO);
		int saved_out = dup(STDOUT_FILENO);
		apply_redirect(cmd);
		exec = gnl_to_array(cmd->args);
		exec_builtins(&lst_env, &exec, cmd);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return;
	}

	while (cmd)
	{
		exec = gnl_to_array(cmd->args);
		if (cmd->next)
			pipe(fd);
		else 
		{
			fd[0] = STDIN_FILENO;
			fd[1] = STDOUT_FILENO;
		}
		pid = fork();
		if (pid == 0)
			child_process(cmd, in_fd, fd[1], lst_env, env, &exec);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (cmd->next)
			close(fd[1]);
		in_fd = fd[0];
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 1;
}

