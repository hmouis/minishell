/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 04:43:48 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/23 04:44:05 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	existing_pipes(t_final_struct *list)	
{
	if (!list)
		return -1;
	if (list->next == NULL)
		return 0;
	return 1;
}

int	exec_pipe(t_final_struct *list)
{
	int	fd[2];
	int child_pid;

	if (existing_pipes(list) != 1)
		return -1;
	if (pipe(fd) == -1)
		return (perror("pipe:"), -1);
	dup2(fd[1], STDOUT_FILENO);
	return 1;
}
