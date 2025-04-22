/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:50:08 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/04/22 14:28:42 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return 0;
	while (s[i])
		i++;
	return i;
}

int	builtin_command(t_lst *list, char **bu_command)
{
	int	i;

	i = 0;
	if (!list->content)
		return 0;
	while (bu_command[i])
	{
		if (!ft_strcmp(list->content, bu_command[i]))
			return 1;
		i++;
	}
	return 0;
}

int	external_command(t_lst *list, char **external_command)
{
	int	i;

	i = 0;
	if (!list->content)
		return 0;
	while (external_command[i])
	{
		if (!ft_strcmp(list->content, external_command[i]))
			return 1;
		i++;
	}
	return 0;

}

int	is_redirection(t_lst *list, char **opr)
{
	if (!list->content)
		return 0;
	int	i;

	i = 0;
	while (opr[i])
	{
		if (!ft_strcmp(list->content, opr[i]))
			return 1;
		i++;
	}
	return 0;
}

int	is_env_variable(t_lst *list)
{
	if (!list->content)
		return 0;
	return (list->content[0] == '$');
}

int	is_quoted_string(t_lst *list)
{
	if (!list->content)
		return 0;
	char	*s;
	int	length;

	length = 0;
	s = list->content;
	length = len(s);
	return ((s[0] == '\'' && s[length - 1] == '\'') || (s[0] == '"' && s[length - 1] == '"'));
}

int	is_pipe(t_lst *list)
{
	if (!list->content)
		return 0;
	if (!ft_strcmp(list->content, "|"))
		return 1;
	return 0;
}

void	tokens_type(t_lst **list)
{
	char	*bu_command[] = {"cd", "echo", "pwd", "export", "unset","env","exit", NULL};
	char	*ect_command[] = {"ls", "cat", "grep", NULL};
	char	*opr[] = {"<", ">", ">>", NULL};
	if (builtin_command(*list, bu_command))
		(*list)->type = "builtin command";
	else if (external_command(*list, ect_command))
		(*list)->type = "command";
	else if (is_redirection(*list, opr))
		(*list)->type = "redirection";
	else if (is_env_variable(*list))
		(*list)->type = "environment variable";
	else if (is_quoted_string(*list))
		(*list)->type = "quoted string";
	else if (is_pipe(*list))
		(*list)->type = "pipe";
	else
		(*list)->type = "argument";
}
