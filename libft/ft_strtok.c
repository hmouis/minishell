/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:12:48 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:36:59 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtok(char *str, char *delim)
{
	static char	*last_word;
	char		*token_start;

	if (str == NULL)
		str = last_word;
	if (str == NULL)
		return (NULL);
	while (*str && ft_strchr(delim, *str))
		++str;
	if (*str == '\0')
	{
		last_word = NULL;
		return (NULL);
	}
	token_start = str;
	while (*str && !ft_strchr(delim, *str))
		++str;
	if (*str)
	{
		*str = '\0';
		last_word = str + 1;
	}
	else
		last_word = NULL;
	return (token_start);
}
