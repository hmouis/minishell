/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:25:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/29 17:37:31 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input(int *fd, char *file, int *input_redirected)
{
	char	*msg;
	char	*full;

	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		msg = ft_strjoin("minishell: ", file);
		full = ft_strjoin(msg, "");
		perror(full);
		exit(1);
	}
	dup2(*fd, STDIN_FILENO);
	close(*fd);
	*input_redirected = 1;
}

void	handle_output(int *fd, char *file, int *output_redirected)
{
	char	*msg;
	char	*full;

	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		msg = ft_strjoin("minishell: ", file);
		full = ft_strjoin(msg, "");
		perror(full);
		exit(1);
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
	*output_redirected = 1;
}

void	handle_append(int *fd, char *file, int *output_redirected)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		g_exit_status = 1;
		exit(1);
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
	*output_redirected = 1;
}

void split_handle_herdoc(int fd2, t_herdoc *herdoc)
{
	ssize_t count;

	count = 0;
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
}

void	handle_her_doc(int *fd, char *file, t_herdoc *herdoc,
		int *input_redirected)
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
	split_handle_herdoc(fd2, herdoc);
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
	*input_redirected = 1;
}

int	apply_redirect(t_final_struct *tmp, int *input_redirected,
		int *output_redirected)
{
	t_apply_red	vars;
	char	*file;

	vars.flag = 0;
	if (!pars_red(tmp->redirect))
		return (-1);
	while (tmp->redirect)
	{
		vars.redirect = tmp->redirect->type;
		file = tmp->redirect->next->str;
		if (tmp->redirect->next->type == var && file[0] == '\0')
			return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), -1);
		if (vars.redirect == op_redirect_input)
			handle_input(&vars.fd, file, input_redirected);
		else if (vars.redirect == op_redirect_output)
			handle_output(&vars.fd, file, output_redirected);
		else if (vars.redirect == op_append)
			handle_append(&vars.fd, file, output_redirected);
		else if (vars.flag == 0 && vars.redirect == op_herdoc)
			vars.flag = 1, (handle_her_doc(&vars.fd, file, tmp->herdoc,
						input_redirected));
		tmp->redirect = tmp->redirect->next->next;
	}
	return (0);
}