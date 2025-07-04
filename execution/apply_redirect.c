/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:25:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/01 15:48:27 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/expansions.h"

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

void	handle_her_doc(int *fd, char *file, t_herdoc *herdoc,
		int *input_redirected)
{
	int		fd2;
	ssize_t	count;

	count = 0;
	if (access(file, F_OK) == 0)
		file = char_join(file, str_len(file), '0');
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
	char		*file;

	vars.flag = 0;
	if (!pars_red(tmp->redirect))
		return (-1);
	while (tmp->redirect)
	{
		assigned_var(tmp, &file, &vars);
		if (tmp->redirect->next->type == var && file[0] == '\0')
			return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), -1);
		if (vars.redirect == op_redirect_input)
			handle_input(&vars.fd, file, input_redirected);
		else if (vars.redirect == op_redirect_output)
			handle_output(&vars.fd, file, output_redirected);
		else if (vars.redirect == op_append)
			handle_append(&vars.fd, file, output_redirected);
		else if (vars.flag == 0 && vars.redirect == op_herdoc)
		{
			vars.flag = 1;
			handle_her_doc(&vars.fd, file, tmp->herdoc, input_redirected);
		}
		tmp->redirect = tmp->redirect->next->next;
	}
	return (0);
}
