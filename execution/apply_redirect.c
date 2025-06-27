/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:25:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/26 11:31:17 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append_(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open for append");
		return (-1);
	}
	return (fd);
}

void	handle_input(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		char *msg = ft_strjoin("minishell: ", file);
		char *full = ft_strjoin(msg, ": ");
		perror(full);
		exit(1);
	}
	dup2(*fd, STDIN_FILENO);
	close(*fd);
}

void	handle_output(int *fd, char *file)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		perror("");
		return ;
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void	handle_append(int *fd, char *file)
{
	*fd = append_(file);
	if (*fd < 0)
	{
		perror("");
		return ;
	}
	close(*fd);
	dup2(*fd, STDOUT_FILENO);
}

void	handle_her_doc(int *fd, char *file, t_herdoc *herdoc)
{
	int		fd2;
	ssize_t	count;

	count = 0;
	fd2 = open(file, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd2 < 0)
	{
		perror("open");
		exit(1);
	}
	while (herdoc)
	{
		if (!herdoc->next)
			break ;
		herdoc = herdoc->next;
	}
	while (herdoc->list)
	{
		count = write(fd2, herdoc->list->str, str_len(herdoc->list->str));
		if (count < 0)
		{
			perror("write");
			close(fd2);
			exit(1);
		}
		herdoc->list = herdoc->list->next;
	}
	close(fd2);
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		perror("open read");
		exit(1);
	}
	unlink(file);
	dup2(*fd, STDIN_FILENO);
	close(*fd);
}

int apply_redirect(t_final_struct *tmp, int *input_redirected)
{
	int		fd;
	int		redirect;
	char	*file;
	int		flag;

	flag = 0;
	*input_redirected = 0;

	if (!pars_red(tmp->redirect))
		return (-1);

	while (tmp->redirect)
	{
		redirect = tmp->redirect->type;
		file = tmp->redirect->next->str;

		if (tmp->redirect->next->type == var && file[0] == '\0')
			return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), -1);

		if (redirect == op_redirect_input)
		{
			handle_input(&fd, file);
			*input_redirected = 1;
		}
		else if (redirect == op_redirect_output)
		{
			handle_output(&fd, file);
		}
		else if (redirect == op_append)
		{
			handle_append(&fd, file);
		}
		else if (flag == 0 && redirect == op_herdoc)
		{
			flag = 1;
			handle_her_doc(&fd, file, tmp->herdoc);
			*input_redirected = 1;
		}
		tmp->redirect = tmp->redirect->next->next;
	}
	return (0);
}

