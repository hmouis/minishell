/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:25:25 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/07 11:06:11 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pipe_line(t_lst *lst)
{
	char	*err_msg;

	err_msg = NULL;
	if (lst->type == op_pipe)
		return (lst->content);
	while (lst)
	{
		while (lst && lst->type == word)
		{
			err_msg = check_quote(lst->content);
			if (err_msg)
				return (err_msg);
			lst = lst->next;
		}
		err_msg = simple_command(&lst);
		if (err_msg)
			return (err_msg);
	}
	return (NULL);
}

char *check_quote(char *str)
{
	int i;
	char quote;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == '\0')
				return ("end of file");
		}
		i++;
	}
	return(NULL);
}

char	*simple_command(t_lst **lst)
{
	if (*lst && (*lst)->type != op_pipe)
	{
		if (!(*lst)->next)
			return ("newline");
		if ((*lst)->next && (*lst)->next->type != word)
			return ((*lst)->next->content);
		*lst = (*lst)->next;
	}
	else if (*lst && (*lst)->type == op_pipe)
	{
		if (!(*lst)->next)
			return ("end of file");
		if ((*lst)->next->type == op_pipe)
			return ((*lst)->next->content);
		*lst = (*lst)->next;
	}
	return (NULL);
}

t_lst	*new_node_c(t_lst *node)
{
	t_lst *new_node;

	new_node = ft_malloc(sizeof(t_lst), 1);
	if (!new_node)
		return (NULL);
	new_node->content = node->content;
	new_node->type = node->type;
	new_node->next = NULL;
	return (new_node);	
}

void add_to_lst_c(t_lst **lst, t_lst *node)
{
	t_lst *new_node;

	new_node =  new_node_c(node);
	add_back(lst, new_node);
}

t_cmd	*creat_cmd_struct(t_cmd **cmd, t_lst *lst)
{
	t_cmd	*head;

	*cmd = node(lst);
	head = *cmd;
	while (lst)
	{
		while (lst && lst->type == word)
		{
			add_to_lst_c(&(*cmd)->arg, lst);
			lst = lst->next;
		}
		if (lst && lst->type != op_pipe)
		{
			add_to_lst_c(&(*cmd)->redirect, lst);
			lst = lst->next;
			add_to_lst_c(&(*cmd)->redirect, lst);
			lst = lst->next;
		}
		if (lst && lst->type == op_pipe)
		{
			(*cmd)->next = node(lst);
			*cmd = (*cmd)->next;
			lst = lst->next;
		}
	}
	return (head);
}

