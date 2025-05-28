/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:23:12 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/25 16:37:52 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_of_redirect(char *redirect)
{
	if (!redirect)
		return -1;
	if (ft_strcmp(redirect, "<") == 0)
		return op_redirect_input;
	else if (ft_strcmp(redirect, ">") == 0)
		return op_redirect_output;
	else if (ft_strcmp(redirect, ">>") == 0)
		return op_append;
	return -1;
}

void	append_(char* filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open for append");
		return;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	apply_redirect(char *file, int redirect)
{
	int	fd;

	if (!file)
		return -1;
	if (redirect == op_redirect_input)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			perror("open:");
			return -1;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		return 1;
	}
	else if (redirect == op_redirect_output)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open:");
			return -1;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return 1;
	}
	else if (redirect == op_append)
	{
		append_(file);
		return 1;
	}
	return -1;
}

