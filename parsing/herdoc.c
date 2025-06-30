/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:26:08 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 20:48:16 by hmouis           ###   ########.fr       */
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
		new_str = char_join(new_str, str_len(new_str), str[i]);
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
	char	*new_line;

	new_line = NULL;
	var = NULL;
	if (flag)
	{
		new_line = char_join(line, str_len(line), '\n');
		add_to_gnl_lst(lst, new_line, -1);
	}
	else
	{
		var = expand_herdoc(line, env);
		var = char_join(var, str_len(var), '\n');
		add_to_gnl_lst(lst, var, -1);
	}
}

int	ft_getc(FILE *stream)
{
	char	c;

	(void)stream;
	if (g_exit_status == 130)
		return (EOF);
	if (read(0, &c, 1) <= 0)
		return (EOF);
	return (c);
}

t_herdoc	*fill_herdoc(t_lst *redirect, t_env *env, t_herdoc **herdoc)
{
	int			remainder;
	t_herdoc	*head;
	extern int	g_in_heredoc;

	remainder = 0;
	*herdoc = new_herdoc();
	head = *herdoc;
	while (redirect)
	{
		if (!ft_strcmp("<<", redirect->content))
		{
			allocate_herdoc(&remainder, herdoc);
			redirect = redirect->next;
			rl_getc_function = ft_getc;
			(*herdoc)->list = her_doc(redirect->content, env, (*herdoc)->list);
			rl_getc_function = rl_getc;
			if (!(*herdoc)->list && g_exit_status == 130)
				return (NULL);
			else
				add_to_gnl_lst(&(*herdoc)->list, "", -1);
			change_value(1);
		}
		redirect = redirect->next;
	}
	return (head);
}
