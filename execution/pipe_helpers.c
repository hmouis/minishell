/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:23:39 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 02:24:04 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal_exit(int wstatus, int pid, int last_pid)
{
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGINT || WTERMSIG(wstatus) == SIGQUIT)
			write(2, "\n", 1);
	}
	if (pid == last_pid)
	{
		if (WIFEXITED(wstatus))
			g_exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			g_exit_status = 128 + WTERMSIG(wstatus);
		else if (WIFSTOPPED(wstatus))
			g_exit_status = 128 + WSTOPSIG(wstatus);
	}
}

void	wait_for_children(int pid, int last_pid, int wstatus)
{
	int	track_sig;

	track_sig = 0;
	pid = wait(&wstatus);
	while (pid > 0)
	{
		if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGINT || WTERMSIG(wstatus) == SIGQUIT)
				track_sig = 1;
		}
		handle_signal_exit(wstatus, pid, last_pid);
		pid = wait(&wstatus);
	}
	if (track_sig)
		write(2, "\n", 1);
}

void	initialize_fds(int *in_fd, int *out_fd)
{
	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
}
