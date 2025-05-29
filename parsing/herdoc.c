/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:46:07 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/24 12:59:57 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *expand_herdoc(char *str, t_env *env)
{
	char *new_str = NULL;
	char *var_str = NULL;
	char *tmp = NULL;
	int i = 0;
	int len = 0;
	int start = 0;

	while (str && str[i])
	{
		if (str[i] == '$' && check_char(str[i + 1]))
		{
			start = i;
			i++;
			len++;
			while (str[i] && var_char(str[i]))
			{
				i++;
				len++;
			}
			var_str = ft_strlcpy(var_str, str, len, start);
			tmp = get_env(var_str + 1, env);
			if (tmp)
				new_str = ft_strjoin(new_str, tmp);
			tmp = NULL;
			var_str = NULL;
			continue;
		}
		new_str = char_join(new_str, str_len(new_str) + 1, str[i]);
		i++;
	}
	return (new_str);
}

void put_error_msg(char *str)
{
	printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", str);
}

t_herdoc *new_herdoc()
{
	t_herdoc *node;

	node = ft_malloc(sizeof(t_herdoc) ,1);
	if (!node)
		return (NULL);
	node->list = NULL;
	node->next = NULL;
	return (node);
}

char *remove_quotes(char *str)
{
	int i = 0;
	char quote;
	char *new_str = NULL;

	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
			{
				new_str = char_join(new_str, str_len(new_str) + 1, str[i]);
				i++;
			}
			i++;
			continue;
		}
		new_str = char_join(new_str, str_len(new_str) + 1, str[i]);
		i++;
	}
	if (!new_str)
		return (ft_strdup(""));
	return (new_str);
}

t_gnl *empty_line(char *line, t_gnl *lst, char *del)
{
	if (!line)
		put_error_msg(del);
	return (lst);
}

void fill_lst(char *line, int flag, t_env *env, t_gnl **lst)
{
	char *var;

	var = NULL;
	if (flag)
	{
		line = char_join(line, str_len(line) + 1, '\n');	
		add_to_gnl_lst(lst, line, -1);
	}
	else
	{
		var = expand_herdoc(line, env);
		var	= char_join(var, str_len(var) + 1, '\n');	
		add_to_gnl_lst(lst, var, -1);
	}

}

t_gnl *her_doc(char *del, t_env * env, t_gnl *lst)
{
	char *line;
	int flag;

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

t_herdoc *fill_herdoc(t_lst *redirect, t_env *env, t_herdoc **herdoc)
{
	int remainder = 0;
	t_herdoc *head = NULL;

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













