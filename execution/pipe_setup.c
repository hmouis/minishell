/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:27:09 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 02:27:27 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_invalid_pipe_redirect(t_final_struct *list, t_env *lst_env,
		t_exec_pipe **var)
{
	t_exec	*exec;

	*var = ft_malloc(sizeof(t_exec_pipe), 1);
	if (!*var)
		exit(1);
	if (list && !list->next && list->args && is_builtins(list->args->str) != -1
		&& !list->redirect)
	{
		exec = gnl_to_array(list->args);
		exec_builtins(&lst_env, &exec, list);
		return (1);
	}
	return (0);
}

void	run_in_child(t_child_params *params, t_exec **exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (params->fnl->next)
		close(params->var->fd[0]);
	child_process(params, exec);
}

void	setup_pipes_and_fork(t_final_struct *list, t_exec_pipe *var,
		t_child_params *params, t_exec *exec)
{
	if (list->next)
		pipe(var->fd);
	else
		initialize_fds(&var->fd[0], &var->fd[1]);
	var->pid = fork();
	if (var->pid == 0)
		run_in_child(params, &exec);
}
