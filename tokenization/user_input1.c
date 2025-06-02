/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:09:07 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/02 11:48:19 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char *str)
{
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

int	valid_operator(char c1, char c2)
{
	return (c1 == c2 && (c1 == '<' || c1 == '>'));
}

int	token_quote(int *i, char *input, t_lst **lst, t_var *var)
{
	char	c;

	c = input[*i];
	if (c != '"' && c != '\'')
		return (0);
	while (input[*i])
	{
		(*i)++;
		var->length++;
		if (input[*i] && input[*i] == c)
		{
			(*i)++;
			var->length++;
			break ;
		}
	}
	return (1);
}

int	token_dollar_sign(int *i, char *input, t_lst **lst, t_var *var)
{
	if (input[*i] != '$')
		return (0);
	while (input[*i])
	{
		if (token_quote(i, input, lst, var))
			continue ;
		if (white_space(input[*i]) || charchr("<>|", input[*i]))
			break ;
		var->length++;
		(*i)++;
	}
	return (1);
}
