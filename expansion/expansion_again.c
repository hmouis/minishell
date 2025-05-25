/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_again.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:36:51 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/21 13:43:35 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_new_exp *new_lst_node()
{
	t_new_exp *new_node;

	new_node = ft_malloc(sizeof(t_new_exp), 1);
	if (!new_node)
		return (NULL);
	new_node->string = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	*new_node_(char *content, int flag)
{
	t_lst	*node;

	node = ft_malloc(sizeof(t_lst), 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->type = flag;
	node->next = NULL;
	return (node);
}

static void	add_to_string_lst(t_lst **lst, char *content, int flag)
{
	t_lst	*node;

	node = new_node_(content, flag);
	add_back(lst, node);
}

int check_char(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}


int split_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}


void split_string(char *str, t_new_exp **exp)
{
	int i = 0;
	int start = 0;
	int len = 0;
	char *new_str = NULL;
	char quote;
	int flag = 0;

	start = i;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '$')
		{
			if (len > 0)
			{
				new_str = ft_strlcpy(new_str, str, len, start);
				if (str[start] == '$' && check_char(str[start + 1]))
					flag = 6;
				else
					flag = 7;
				add_to_string_lst(&(*exp)->string, new_str, flag);
				new_str = NULL;
				start = i;
				len = 0;
			}
			if (is_quote(str[i]))
			{
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote)
				{
					i++;
					len++;
				}
				i++;
				new_str = ft_strlcpy(new_str, str, len, start + 1);
				if (quote == '"')
					flag = 9;
				else 
					flag = 8;
				add_to_string_lst(&(*exp)->string, new_str, flag);
				new_str = NULL;
				start = i;
				len = 0;
				continue;
			}
			else if (str[i] == '$')
			{
				i++;
				len++;
				if (check_char(str[i]))
					flag = 6;
				else
					flag = 7;
				while (str[i] && var_char(str[i]))
				{
					i++;
					len++;
				}
				new_str = ft_strlcpy(new_str, str, len, start);
				add_to_string_lst(&(*exp)->string, new_str, flag);
				new_str = NULL;
				start = i;
				len = 0;
				continue;
			}
		}
		i++;
		len++;
	}
	if (len > 0)
	{
		if (str[start] == '$' && check_char(str[start + 1]))
			flag = 6;
		else
			flag = 7;
		new_str = ft_strlcpy(new_str, str, len, start);
		add_to_string_lst(&(*exp)->string, new_str, flag);
		new_str = NULL;
		start = i;
		len = 0;
	}
}

t_final_struct *fnl_node()
{
	t_final_struct *new_node;

	new_node = ft_malloc(sizeof(t_final_struct), 1);
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->redirect = NULL;
	new_node->herdoc= NULL;
	new_node->next = NULL;
	return (new_node);
}

t_final_struct *creat_new_exp(t_env *list, t_new_exp **exp, t_cmd *cmd, t_final_struct **fnl)
{
	t_final_struct *head;
	t_new_exp *tmp = NULL;

	*fnl = fnl_node();
	head = *fnl;
	while (cmd)
	{
		if (cmd->arg)
		{
			*exp = new_lst_node();
			tmp = *exp;
		}
		while (cmd->arg)
		{
			split_string(cmd->arg->content, exp);
			cmd->arg = cmd->arg->next;
			(*exp)->next = new_lst_node();
			*exp = (*exp)->next;
			if (!cmd->arg)
				expand(tmp, list, &(*fnl)->args);
		}
		*exp = NULL;
		tmp = NULL;
		if (cmd->redirect)
		{
			*exp = new_lst_node();
			tmp = *exp;
		}
		while (cmd->redirect)
		{
			split_string(cmd->redirect->content, exp);
			cmd->redirect = cmd->redirect->next;
			(*exp)->next = new_lst_node();
			*exp = (*exp)->next;
			if (!cmd->redirect)
				expand(tmp, list, &(*fnl)->redirect);
		}
		cmd = cmd->next;
		if (cmd)
		{
			(*fnl)->next = fnl_node();
			*fnl = (*fnl)->next;
		}
	}
	return (head);
}
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
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
char *expand_double_quote(char *str, t_env *env)
{
	int i = 0;
	t_new_exp *exp = NULL;
	char *new_str = NULL;
	char *tmp = NULL;
	int start = 0;
	int len = 0;
	int flag = 0;

	exp = new_lst_node();
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (len > 0)
			{
				new_str = ft_strlcpy(new_str, str, len, start);
				if (str[start] == '$' && check_char(str[start + 1]))
					flag = 6;
				else
					flag = 7;
				add_to_string_lst(&exp->string, new_str, flag);
				new_str = NULL;
				start = i;
				len = 0;
			}
			i++;
			len++;
			if (check_char(str[i]))
				flag = 6;
			else
				flag = 7;
			while (str[i] && var_char(str[i]))
			{
				i++;
				len++;
			}
			new_str = ft_strlcpy(new_str, str, len, start);
			add_to_string_lst(&exp->string, new_str, flag);
			new_str = NULL;
			start = i;
			len = 0;
			continue;
		}
		i++;
		len++;
	}
	if (len > 0)
	{
		new_str = ft_strlcpy(new_str, str, len, start);
		if (str[start] == '$' && check_char(str[start + 1]))
			flag = 6;
		else
			flag = 7;
		add_to_string_lst(&exp->string, new_str, flag);
		new_str = NULL;
		start = i;
		len = 0;
	}
	while (exp && exp->string)
	{
		if (exp->string->type == var)
		{
			tmp = get_env(exp->string->content + 1, env);
			if (!tmp)
				exp->string->content[0] = '\0';
			new_str = ft_strjoin(new_str, tmp);
		}
		else
			new_str = ft_strjoin(new_str, exp->string->content);
		exp->string = exp->string->next;
	}
	return (new_str);
}
t_gnl *final_node(char *content)
{
	t_gnl *new_node;

	new_node = ft_malloc(sizeof(t_gnl), 1);
	if (!new_node)
		return (NULL);
	new_node->str = content;
	new_node->next = NULL;
	return (new_node);
}

t_gnl	*last_node_gnl(t_gnl *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_gnl_back(t_gnl **lst, t_gnl *node)
{
	t_gnl	*last;

	if (!lst || !node)
		return ;
	if (*lst)
	{
		last = last_node_gnl(*lst);
		last->next = node;
	}
	else
	*lst = node;
}

void add_to_gnl_lst(t_gnl **lst, char *content)
{
	t_gnl *node;

	node = final_node(content);
	add_gnl_back(lst, node);
}

int split_var_arg(char *str, char **field_str)
{
	int i = 0;
	int count = 0;
	int remainder = 0;
	int check = 0;

	while (str && str[i])
	{
		if (split_char(str[i]))
		{
			i++;
			remainder = 1;
			check = 1;
			continue;
		}
		count++;
		if (remainder == 1)
		{
			*field_str = char_join(*field_str, count, ' ');
			count++;
			remainder = 0;
		}
		*field_str = char_join(*field_str, count, str[i]);
		i++;
	}
	if (remainder == 1)
		*field_str = char_join(*field_str, count + 1, ' ');
	return (check);
}

void expand(t_new_exp *exp, t_env *env, t_gnl **gnl)
{
	char *str = NULL;
	char *tmp = NULL;
	char *field_str = NULL;
	int i = 0;
	int j = 0;

	while (exp)
	{
		while (exp->string)
		{
			if (exp->string->type == var)
			{
				tmp = get_env(exp->string->content + 1, env);
				if (!tmp)
					exp->string->content[0] = '\0';
				if (!split_var_arg(tmp, &field_str))
					str = ft_strjoin(str, field_str);
				else
				{
					i = 0;
					if (str && field_str[i] == ' ')
					{
						add_to_gnl_lst(gnl, str);
						str = NULL;
					}
					while (field_str[i])
					{
						while (field_str[i] && field_str[i] == ' ')
							i++;
						while (field_str[i] && field_str[i] != ' ')
						{
							str = char_join(str, str_len(str) + 1, field_str[i]);
							i++;
						}
						if (field_str[i] == ' ')
						{
							add_to_gnl_lst(gnl, str);
							str = NULL;
						}
					}
				}
				field_str = NULL;
			}
			else if (exp->string->type == double_quote)
			{
				str = ft_strjoin(str, expand_double_quote(exp->string->content ,env));
				if(str == NULL)
					str = ft_strdup("");
			}else
				str = ft_strjoin(str, exp->string->content);
			exp->string = exp->string->next;
		}
		if (str)
			add_to_gnl_lst(gnl, str);
		exp = exp->next;
		str = NULL;
	}

}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s2)
		return (s1);
	new = ft_malloc(sizeof(char) * (str_len(s1) + str_len(s2) + 1), 1);
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
char *char_join(char *str, int count, char c)
{
	int j = 0;
	char *new_str;
	new_str = ft_malloc(sizeof(char) * count + 1, 1);
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
