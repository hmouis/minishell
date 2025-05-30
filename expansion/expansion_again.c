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

t_new_exp *new_lst_node(int type)
{
	t_new_exp *new_node;

	new_node = ft_malloc(sizeof(t_new_exp), 1);
	if (!new_node)
		return (NULL);
	new_node->string = NULL;
	new_node->type = type;
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

void del_last_str(char *str, int *start, int i, int *len, t_new_exp **exp)
{
	char *new_str;
	int flag;

	new_str = NULL;
	new_str = ft_strlcpy(new_str, str, *len, *start);
	flag = 0;
	if (str[*start] == '$' && check_char(str[*start + 1]))
		flag = 6;
	else
		flag = 7;
	add_to_string_lst(&(*exp)->string, new_str, flag);
	new_str = NULL;
	*start = i;
	*len = 0;
}

int quote_string(char *str, int *start, int *i, int *len, t_new_exp **exp)
{
	char quote;
	int flag;
	char *new_str;

	flag = 0;
	new_str = NULL;
	if (!is_quote(str[*i]))
		return (0);
	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		(*i)++;
		(*len)++;
	}
	(*i)++;
	new_str = ft_strlcpy(new_str, str, *len, *start + 1);
	if (quote == '"')
		flag = 9;
	else 
		flag = 8;
	add_to_string_lst(&(*exp)->string, new_str, flag);
	new_str = NULL;
	*start = *i;
	*len = 0;
	return (1);
}

int dollar_sign_string(char *str, int *start, int *i, int *len, t_new_exp **exp)
{
	int flag;
	char *new_str;

	new_str = NULL;
	flag = 0;
	if (str[*i] != '$')
		return (0);
	(*i)++;
	(*len)++;
	if (check_char(str[*i]))
		flag = 6;
	else
		flag = 7;
	while (str[*i] && var_char(str[*i]))
	{
		(*i)++;
		(*len)++;
	}
	new_str = ft_strlcpy(new_str, str, *len, *start);
	add_to_string_lst(&(*exp)->string, new_str, flag);
	new_str = NULL;
	*start = *i;
	*len = 0;	
	return (1);
}

void split_string(char *str, t_new_exp **exp)
{
	int i;
	int start;
	int len;

	i = 0;
	len = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '$')
		{
			if (len > 0)
				del_last_str(str, &start, i, &len, exp);
			if (quote_string(str, &start, &i, &len, exp))
				continue;
			else if (dollar_sign_string(str, &start, &i, &len, exp))
				continue;
		}
		i++;
		len++;
	}
	if (len > 0)
		del_last_str(str, &start, i, &len, exp);
}

t_final_struct *fnl_node()
{
	t_final_struct *new_node;

	new_node = ft_malloc(sizeof(t_final_struct), 1);
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->redirect = NULL;
	new_node->herdoc = NULL;
	new_node->next = NULL;
	return (new_node);
}

int redirect_type(char *str)
{
	if (str && !ft_strcmp(str, "<<"))
		return (2);
	if (str && !ft_strcmp(str, "<"))
		return (0);
	if (str && !ft_strcmp(str, ">>"))
		return (3);
	if (str && !ft_strcmp(str, ">"))
		return (1);
	return (-1);
}

void fnl_argm(t_env *list, t_lst *argm, t_new_exp **exp, t_final_struct **fnl)
{
	t_new_exp *tmp;

	*exp = new_lst_node(-1);
	tmp = *exp;
	while (argm)
	{
		split_string(argm->content, exp);
		argm = argm->next;
		if (!argm)
			expand(tmp, list, &(*fnl)->args);
		(*exp)->next = new_lst_node(-1);
		*exp = (*exp)->next;
	}
}

void fnl_red(t_env *list, t_lst *red, t_new_exp **exp, t_final_struct **fnl)
{
	t_new_exp *tmp;

	*exp = new_lst_node(redirect_type(red->content));
	tmp = *exp;
	while (red)
	{
		split_string(red->content, exp);
		red = red->next;
		if (!red)
		{
			expand(tmp, list, &(*fnl)->redirect);
			continue;
		}
		(*exp)->next = new_lst_node(redirect_type(red->content));
		*exp = (*exp)->next;
	}
}

t_final_struct *creat_new_exp(t_env *list, t_new_exp **exp, t_cmd *cmd, t_final_struct **fnl)
{
	t_final_struct *head;
	t_lst *argm;
	t_lst *red;

	*fnl = fnl_node();
	head = *fnl;
	argm = NULL;
	red = NULL;
	while (cmd)
	{
		argm = cmd->arg;
		red = cmd->redirect;
		if (argm)
			fnl_argm(list, argm, exp, fnl);
		if (red)
			fnl_red(list, red, exp, fnl);
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

void skip_var_char(char *str, int *i, int *len)
{
	while (str[*i] && var_char(str[*i]))
	{
		(*i)++;
		(*len)++;
	}
}

int	dollar_sign_in_quote(char *str, int *start, int *i, int *len, t_new_exp **exp)
{
	int flag;
	char *new_str;

	new_str = NULL;
	flag = 0;
	if (str[*i] != '$')
		return (0);
	if (*len > 0)
		del_last_str(str, start, *i, len, exp);
	(*i)++;
	(*len)++;
	if (check_char(str[*i]))
		flag = 6;
	else
		flag = 7;
	if (str[*i] && var_char(str[*i]))
		skip_var_char(str, i, len);
	new_str = ft_strlcpy(new_str, str, *len, *start);
	add_to_string_lst(&(*exp)->string, new_str, flag);
	new_str = NULL;
	*start = *i;
	*len = 0;
	return (1);
}

char *fnl_str(t_env *env, t_new_exp *exp)
{
	char *new_str;
	char *tmp;

	tmp = NULL;
	new_str = NULL;
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

char *expand_double_quote(char *str, t_env *env)
{
	int i;
	t_new_exp *exp;
	int start;
	int len;

	len = 0;
	i = 0;
	start = 0;
	exp = NULL;
	exp = new_lst_node(-1);
	while (str[i])
	{
		if (dollar_sign_in_quote(str, &start, &i, &len, &exp))
			continue;
		i++;
		len++;
	}
	if (len > 0)
		del_last_str(str, &start, i, &len, &exp);
	return (fnl_str(env, exp));
}

t_gnl *final_node(char *content, int type)
{
	t_gnl *new_node;

	new_node = ft_malloc(sizeof(t_gnl), 1);
	if (!new_node)
		return (NULL);
	new_node->str = content;
	new_node->type = type;
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

void add_to_gnl_lst(t_gnl **lst, char *content, int type)
{
	t_gnl *node;

	node = final_node(content, type);
	add_gnl_back(lst, node);
}

int skip_split_char(char *str, int *i, int *remainder, int *check)
{
	if (!split_char(str[*i]))
		return (0);
	(*i)++;
	*remainder = 1;
	*check = 1;
	return (1);
}

void add_space(char **field_str, int *remainder, int *count)
{
	*field_str = char_join(*field_str, *count, ' ');
	(*count)++;
	*remainder = 0;
}

int split_var_arg(char *str, char **field_str)
{
	int i;
	int count;
	int remainder;
	int check;

	i = 0;
	check = 0;
	remainder = 0;
	count = 0;
	while (str && str[i])
	{
		if (skip_split_char(str, &i, &remainder, &check))
			continue;
		count++;
		if (remainder == 1)
			add_space(field_str, &remainder, &count);
		*field_str = char_join(*field_str, count, str[i]);
		i++;
	}
	if (remainder == 1)
		*field_str = char_join(*field_str, count + 1, ' ');
	return (check + remainder);
}

void split_str(char **str, char *field_str, t_gnl **gnl, t_new_exp *exp)
{
	int i;

	i = 0;
	if (*str && field_str[i] == ' ')
	{
		add_to_gnl_lst(gnl, *str, exp->type);
		*str = NULL;
	}
	while (field_str[i])
	{
		while (field_str[i] && field_str[i] == ' ')
			i++;
		while (field_str[i] && field_str[i] != ' ')
		{
			*str = char_join(*str, str_len(*str) + 1, field_str[i]);
			i++;
		}
		if (field_str[i] == ' ')
		{
			add_to_gnl_lst(gnl, *str, exp->type);
			*str = NULL;
		}
	}
}

void check_double_quote(char **str, t_env *env, t_new_exp *exp)
{
	*str = ft_strjoin(*str, expand_double_quote(exp->string->content ,env));
	if(*str == NULL)
		*str = ft_strdup("");
}

void is_var(t_new_exp *exp, char **str, char **field_str, t_env *env, t_gnl **gnl, int *flag)
{
	char *tmp;

	tmp = NULL;
	tmp = get_env(exp->string->content + 1, env);
	if (!tmp)
		exp->string->content[0] = '\0';
	*flag = split_var_arg(tmp, field_str);
	if (!*flag)
		*str = ft_strjoin(*str, *field_str);
	else
		split_str(str, *field_str, gnl, exp);
	*field_str = NULL;
}

void expand(t_new_exp *exp, t_env *env, t_gnl **gnl)
{
	char *str;
	char *field_str;
	int flag = 0;

	field_str = NULL;
	str = NULL;
	while (exp)
	{
		while (exp->string)
		{
			if (exp->string->type == var)
				is_var(exp, &str, &field_str, env, gnl, &flag);
			else if (exp->string->type == double_quote)
				check_double_quote(&str, env, exp);
			else
				str = ft_strjoin(str, exp->string->content);
			exp->string = exp->string->next;
		}
		if (!str && flag != 2)
			str = ft_strdup("");
		flag = 0;
		add_to_gnl_lst(gnl, str, exp->type);
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
