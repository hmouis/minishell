/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:05:17 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 02:05:18 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_redirections(t_final_struct *fnl, t_exec_pipe *var)
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
}

void	child_process(t_child_params *params, t_exec **exec)
{
	setup_redirections(params->fnl, params->var);
	if (!exec || !(*exec) || !(*exec)->args[0])
		exit(0);
	if (is_builtins((*exec)->args[0]) != -1)
	{
		exec_builtins(&params->lst_env, exec, params->fnl);
		exit(EXIT_SUCCESS);
	}
	exec_cmd(params->env, exec, params->lst_env);
	exit(EXIT_FAILURE);
}

void	execute(t_final_struct *list, t_env *lst_env, char **env)
{
	t_exec_pipe		*var;
	t_exec			*exec;
	t_child_params	params;

	if (exec_invalid_pipe_redirect(list, lst_env, &var))
		return ;
	var->last_pid = -1;
	var->in_fd = STDIN_FILENO;
	params.lst_env = lst_env;
	params.env = env;
	params.var = var;
	while (list)
	{
		exec = gnl_to_array(list->args);
		params.fnl = list;
		setup_pipes_and_fork(list, var, &params, exec);
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
