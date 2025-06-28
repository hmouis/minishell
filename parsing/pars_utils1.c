/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:37:06 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/28 12:04:05 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *str, int status)
{
	if (status == 0)
		printf("minishell: syntax error near unexpected token `%s'\n", str);
	else
		printf("%s\n", str);
	g_exit_status = 2;
}

t_cmd	*node(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->arg = NULL;
	cmd->args = NULL;
	cmd->redirect = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	change_value(int value)
{
	static int	in_herdoc = 0;

	if (value == 2)
		return (in_herdoc);
	in_herdoc = value;
	return (in_herdoc);
}

void	handle_sig_herdoc(int sig)
{
	(void)sig;
	change_value(1);
	g_exit_status = 130;
}

t_gnl	*her_doc(char *del, t_env *env, t_gnl *lst)
{
	char	*line;
	int		flag;

	line = NULL;
	flag = 0;
	if (ft_strchr(del, '"') || ft_strchr(del, '\''))
		flag = 1;
	del = remove_quotes(del);
	signal(SIGINT, handle_sig_herdoc);
	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
			return (NULL);
		if (!line || !ft_strcmp(line, del))
			return (empty_line(line, lst, del));
		else if (line[0] == '\0')
		{
			line = char_join(line, 2, '\n');
			add_to_gnl_lst(&lst, line, -1);
		}
		else
			fill_lst(line, flag, env, &lst);
	}
}
