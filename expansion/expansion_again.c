/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_again.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:00:07 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:39:33 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansions.h"

void	fnl_argm(t_env *list, t_lst *argm, t_new_exp **exp,
		t_final_struct **fnl)
{
	t_new_exp	*tmp;

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

void	fnl_red(t_env *list, t_lst *red, t_new_exp **exp, t_final_struct **fnl)
{
	t_new_exp	*tmp;

	*exp = new_lst_node(redirect_type(red->content));
	tmp = *exp;
	while (red)
	{
		split_string(red->content, exp);
		red = red->next;
		if (!red)
		{
			expand(tmp, list, &(*fnl)->redirect);
			continue ;
		}
		(*exp)->next = new_lst_node(redirect_type(red->content));
		*exp = (*exp)->next;
	}
}

t_final_struct	*creat_new_exp(t_env *list, t_new_exp **exp, t_cmd *cmd,
		t_final_struct **fnl)
{
	t_final_struct	*head;
	t_lst			*argm;
	t_lst			*red;

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

void	expand(t_new_exp *exp, t_env *env, t_gnl **gnl)
{
	t_helper_va	va;

	va.flag = 0;
	va.field_str = NULL;
	va.str = NULL;
	while (exp)
	{
		while (exp->string)
		{
			if (exp->string->type == var)
				is_var(exp, &va, env, gnl);
			else if (exp->string->type == double_quote)
				check_double_quote(&va.str, env, exp);
			else
				va.str = ft_strjoin(va.str, exp->string->content);
			exp->string = exp->string->next;
		}
		va.flag = 0;
		add_to_gnl_lst(gnl, va.str, exp->type);
		exp = exp->next;
		va.str = NULL;
	}
}
