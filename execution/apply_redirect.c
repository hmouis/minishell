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

int	append_(char* filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open for append");
		return -1;
	}
	return fd;
}

int	apply_redirect(t_final_struct *struc)
{
	int	fd = -1;
	int	redirect;
	t_final_struct	*tmp = struc;

	while (tmp->redirect)
	{
		if (!tmp->redirect->next)
		{
			ft_putstr_fd("syntax error: missing file for redirection\n", 2);
			return -1;
		}

		redirect = type_of_redirect(tmp->redirect->str);
		if (redirect == op_redirect_input && tmp->redirect->type != -1)
		{
			fd = open(tmp->redirect->next->str, O_RDONLY);
			if (fd < 0)
			{
				perror("minishell");
				return -1;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirect == op_redirect_output && tmp->redirect->type != -1)
		{
			fd = open(tmp->redirect->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("");
				return -1;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirect == op_append && tmp->redirect->type != -1)
		{
			fd = append_(tmp->redirect->next->str);
			if (fd < 0)
				return -1;
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else
			return -1;
		tmp->redirect = tmp->redirect->next->next;
	}
	return 0;
}
