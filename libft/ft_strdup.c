/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:45:34 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:36:44 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/gc.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	ptr = ft_malloc(sizeof(char) * (i + 1), 1);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup_env(char *s)
{
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	ptr = ft_malloc_env(sizeof(char) * (i + 1), 1);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
