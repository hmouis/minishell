/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:36:07 by hmouis            #+#    #+#             */
/*   Updated: 2025/04/18 11:08:24 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int charchr(char *str, int c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char *ft_strlcpy(char *token, char *input, int len, int j)
{
	int	i;

	i = 0;
	token = malloc(sizeof(char) * len + 1);
	if (!token)
		return (NULL);
	while (i < len)
	{
		token[i] = input[j + i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

int white_space(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}
