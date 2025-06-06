/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:46:07 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 11:22:36 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = 0;
	while (str[i])
	{
		if (add_inside_quote(str, &new_str, &i))
			continue ;
		new_str = char_join(new_str, str_len(new_str) + 1, str[i]);
		i++;
	}
	if (!new_str)
		return (ft_strdup(""));
	return (new_str);
}

t_gnl	*empty_line(char *line, t_gnl *lst, char *del)
{
	if (!line)
		put_error_msg(del);
	return (lst);
}

void	fill_lst(char *line, int flag, t_env *env, t_gnl **lst)
{
	char	*var;

	var = NULL;
	if (flag)
	{
		line = char_join(line, str_len(line) + 1, '\n');
		add_to_gnl_lst(lst, line, -1);
	}
	else
	{
		var = expand_herdoc(line, env);
		var = char_join(var, str_len(var) + 1, '\n');
		add_to_gnl_lst(lst, var, -1);
	}
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
	while (1)
	{
		line = readline("> ");
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

t_herdoc	*fill_herdoc(t_lst *redirect, t_env *env, t_herdoc **herdoc)
{
	int			remainder;
	t_herdoc	*head;

	remainder = 0;
	*herdoc = new_herdoc();
	head = *herdoc;
	while (redirect)
	{
		if (!ft_strcmp("<<", redirect->content))
		{
			if (remainder == 0)
				remainder = 1;
			else
			{
				(*herdoc)->next = new_herdoc();
				*herdoc = (*herdoc)->next;
			}
			redirect = redirect->next;
			(*herdoc)->list = her_doc(redirect->content, env, (*herdoc)->list);
			if (!(*herdoc)->list)
				add_to_gnl_lst(&(*herdoc)->list, "", -1);
		}
		redirect = redirect->next;
	}
	return (head);
}
