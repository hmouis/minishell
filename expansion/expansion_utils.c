/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:46:17 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/14 09:35:20 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *replace_empty_var(char *str)
{
	str[0] = '\0';
	return (str);
}

int var_char(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int str_len(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

t_exp *new_var_node(char *content)
{
	t_exp *new_node;

	new_node = malloc(sizeof(t_exp));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->type = 0;
	new_node->next = NULL;
	return (new_node);
}

t_exp	*last_node_var(t_exp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_var_back(t_exp **lst, t_exp *node)
{
	t_exp	*last;

	if (!lst || !node)
		return ;
	if (*lst)
	{
		last = last_node_var(*lst);
		last->next = node;
	}
	else
	*lst = node;
}

void add_to_var_lst(t_exp **lst, char *content)
{
	t_exp *node;

	node = new_var_node(content);
	add_var_back(lst, node);
}

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int tokenize_dollar_sign(t_exp **exp, char *str)
{
	char *new_str;
	int i;
	int len;
	int start;

	i = 0;
	len = 0;
	start = 0;
	new_str = NULL;
	while (str[i])
	{
		if (!var_char(str[i]))
		{
			if ((str[start] == '$' || str[i] == '$' || is_digit(str[start + 1])) && len > 0)
			{
				new_str = ft_strlcpy(new_str, str, len, start);
				start = i;
				len = 0;
				add_to_var_lst(exp, new_str);
				new_str = NULL;
			}
			if (str[i] == '\'')
			{
				i++;
				len++;
				while (str[i] && str[i] != '\'')
				{
					i++;
					len++;
				}
				if (str[i] == '\0')
					return (0);
			}
			if (str[i] == '"')
			{
				if (len > 0)
				{
					new_str = ft_strlcpy(new_str, str, len, start);
					start = i;
					len = 0;
					add_to_var_lst(exp, new_str);
					new_str = NULL;
				}
				i++;
				len++;
				while (str[i] && str[i] != '"')
				{
					i++;
					len++;
				}
				if (str[i] == '\0')
					return (0);
				i++;
				new_str = ft_strlcpy(new_str, str, len + 1, start);
				start = i;
				len = 0;
				add_to_var_lst(exp, new_str);
				new_str = NULL;
				if (str[i] == '\0')
					return (1);
				continue;
			}
		}
		i++;
		len++;
	}
	if (len > 0)
	{
		new_str = ft_strlcpy(new_str, str, len, start);
		add_to_var_lst(exp, new_str);
		new_str = NULL;
		return (1);
	}
	return (1);
}

void expand_quote(t_exp **lst, char *str)
{
	int i = 0;
	int len = 0;
	char *new_str = NULL;
	int start = 0;

	while (str[i])
	{
		if (str[i] == '$')
		{
			if (len > 0)
			{
				new_str = ft_strlcpy(new_str, str, len, start);
				start = i;
				len = 0;
				add_to_var_lst(lst, new_str);
				new_str = NULL;
			}
			i++;
			len++;
			while (str[i] && var_char(str[i]))
			{
				i++;
				len++;
			}
			new_str = ft_strlcpy(new_str, str, len, start);
			start = i;
			len = 0;
			add_to_var_lst(lst, new_str);
			new_str = NULL;
			continue;
		}
		i++;
		len++;
	}
	if (len > 0)
	{
		new_str = ft_strlcpy(new_str, str, len, start);
		add_to_var_lst(lst, new_str);
		new_str = NULL;
	}
}


void type_of_var(t_exp *exp)
{
	while (exp)
	{
		if (exp->content[0] == '$' && !is_digit(exp->content[1]))
			exp->type = var;
		else
			exp->type = string;
		exp = exp->next;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s2)
		return (s1);
	new = malloc(sizeof(char) * (str_len(s1) + str_len(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char *expand_var(t_exp *exp, t_env *env)
{
	char *str;
	char *tmp;
	t_exp *exp_quote = NULL;

	str = NULL;
	tmp = NULL;
	while (exp)
	{
		if (exp->type == var)
		{
			if (!ft_strcmp("$", exp->content))
				str = ft_strjoin(str, exp->content);
			else
			{
				tmp = get_env(exp->content + 1, env);
				if (!tmp)
					exp->content = replace_empty_var(exp->content);
				str = ft_strjoin(str, split_var_arg(tmp));
			}
		}
		else if (exp->content[0] == '"')
		{
			expand_quote(&exp_quote, exp->content);
			while (exp_quote)
			{
				if (exp_quote->content[0] == '$')
				{
					if (!ft_strcmp("$", exp_quote->content))
						str = ft_strjoin(str, exp_quote->content);
					else
					{
						tmp = get_env(exp_quote->content + 1, env);
						if (!tmp)
							exp->content = replace_empty_var(exp->content);
						str = ft_strjoin(str, tmp);
					}
				}
				else
					str = ft_strjoin(str, exp_quote->content);
				exp_quote = exp_quote->next;
			}
		}
		else
			str = ft_strjoin(str, exp->content);
		exp = exp->next;
	}
	if (!str)
		return (NULL);
	return (str);
}

char *char_join(char *str, int count, char c)
{
	int j = 0;
	char *new_str;
	new_str = malloc(sizeof(char) * count + 1);
	if (!new_str)
		return (NULL);
	while (str && str[j])
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = c;
	j++;
	new_str[j] = '\0';
	return (new_str);
}








































