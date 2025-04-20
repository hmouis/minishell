/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:48:20 by hmouis            #+#    #+#             */
/*   Updated: 2025/04/18 11:40:58 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int split_input(char *input, t_lst **lst)
{
	t_var var;

	var.i = 0;
	var.y = 0;
	var.token = NULL;
	var.length = 0;
	while (1)
	{
		if (!input[var.i])
		{
			if (var.length > 0)
			{
				var.token = ft_strlcpy(var.token, input, var.length, var.y);
				add_to_lst(lst, var.token);
				var.token = NULL;
				var.length = 0;
			}
			break;
		}
		if (is_operator(input[var.i]))
		{
			if (var.length > 0)
			{
				var.token = ft_strlcpy(var.token, input, var.length, var.y);
				add_to_lst(lst, var.token);
				var.token = NULL;
				var.length = 0;
				var.y = var.i;
			}
			var.length++;
			if (valid_operator(input[var.i], input[var.i + 1]))
				var.length++;
			var.token = ft_strlcpy(var.token, input, var.length, var.y);
			add_to_lst(lst, var.token);
			var.token = NULL;
			var.i += var.length;
			var.length = 0;
			var.y = var.i;
			continue;
		}
		if (token_quote(&var.i, input, lst, &var))
			continue;
		if (token_dollar_sign(&var.i, input, lst, &var))
			continue;
		if (token_blank(&var, input, lst))
			continue;
		var.i++;
		var.length++;
	}
	return (0);
}

int token_blank(t_var *var, char *input,t_lst **lst)
{
	if (!white_space(input[var->i]))
		return (0);
	if (var->length > 0)
	{
		var->token = ft_strlcpy(var->token, input, var->length, var->y);
		add_to_lst(lst, var->token);
		var->token = NULL;
		var->length = 0;
	}
	while (white_space(input[var->i]))
		var->i++;
	var->y = var->i;
	return (1);
}

int is_operator(char c)
{
	return (charchr("<>|", c));
}

int valid_operator(char c1, char c2)
{
	return (c1 == c2 && (c1 == '<' || c1 == '>'));
}

int token_quote(int *i, char *input, t_lst **lst, t_var *var)
{
	char c;

	c = input[*i];
	if (c != '"' && c != '\'')
		return (0);
	while (input[*i]) //39 = ' && 34 = "
	{
		(*i)++;
		var->length++;
		if (input[*i] == c)
			break;
	}
	(*i)++;
	var->length++;
	return (1);
}

int token_dollar_sign(int *i, char *input, t_lst **lst, t_var *var)
{
	if (input[*i] != '$')
		return (0);
	while (input[*i])
	{
		var->length++;
		(*i)++;
		if (white_space(input[*i]) || is_operator(input[*i]))
			break;
	}
	return (1);
}



