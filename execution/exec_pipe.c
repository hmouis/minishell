/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:25:37 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/28 11:32:15 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_final_struct *fnl, t_exec_pipe *var, t_env *lst_env, char **env, t_exec **exec)
{
	int	input_redirected;
	int	output_redirected;

	input_redirected = 0;
	output_redirected = 0;
	if (apply_redirect(fnl, &input_redirected, &output_redirected) == -1)
		exit(EXIT_FAILURE);
	if (!input_redirected && var->in_fd != STDIN_FILENO)
	{
		dup2(var->in_fd, STDIN_FILENO);
		close(var->in_fd);
	}
	if (!output_redirected && var->fd[1] != STDOUT_FILENO)
	{
		dup2(var->fd[1], STDOUT_FILENO);
		close(var->fd[1]);
	}
	if (is_builtins((*exec)->args[0]) != -1)
	{
		exec_builtins(&lst_env, exec, fnl);
		exit(EXIT_SUCCESS);
	}
	exec_cmd(env, exec, lst_env);
	exit(EXIT_FAILURE);
}

static void	wait_for_children(int pid, int last_pid, int wstatus)
{
	while ((pid = wait(&wstatus)) > 0)
	{
		if (pid == last_pid && WIFEXITED(wstatus))
			g_exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			g_exit_status = 128 + WTERMSIG(wstatus);
		else if (WIFSTOPPED(wstatus))
			g_exit_status = 128 + WSTOPSIG(wstatus);
		if (g_exit_status == 128 + SIGQUIT || g_exit_status == 128 + SIGINT)
			write(2, "\n", 1);
	}
}

static int	exec_invalid_pipe_redirect(t_final_struct *list, t_env *lst_env, t_exec_pipe **var)
{
	*var = ft_malloc(sizeof(t_exec_pipe), 1);
	if (!*var)
		exit(1);
	t_exec	*exec;
	if (list && !list->next && list->args && is_builtins(list->args->str) != -1
		&& !list->redirect)
	{
		exec = gnl_to_array(list->args);
		exec_builtins(&lst_env, &exec, list);
		return 1;
	}
	return 0;
}

static void	initialize_fds(int *in_fd, int *out_fd)
{
	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
}

static void	run_in_child(t_final_struct *list, t_exec_pipe *var, t_env *lst_env, char **env, t_exec **exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (list->next)
		close(var->fd[0]);
	child_process(list, var, lst_env, env, exec);
}

void	execute(t_final_struct *list, t_env *lst_env, char **env)
{
	t_exec_pipe	*var;
	t_exec	*exec;
	if (exec_invalid_pipe_redirect(list, lst_env, &var))
		return ;
	var->last_pid = -1;
	var->in_fd = STDIN_FILENO;
	while (list)
	{
		exec = gnl_to_array(list->args);
		if (list->next)
			pipe(var->fd);
		else
			initialize_fds(&var->fd[0], &var->fd[1]);
		var->pid = fork();
		if (var->pid == 0)
			run_in_child(list, var, lst_env, env, &exec);
		if (var->in_fd != STDIN_FILENO)
			close(var->in_fd);
		if (list->next)
			close(var->fd[1]);
		var->in_fd = var->fd[0];
		var->last_pid = var->pid;
		list = list->next;
	}
	wait_for_children(var->pid, var->last_pid, var->wstatus);
}
