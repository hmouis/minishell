/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:14:06 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/04 14:16:51 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	return 0;
}

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return NULL;
	while (*s)
	{
		if (*s == c)
			return s;
		s++;
	}
	if (*s == c)
		return s;
	return NULL;
}

int	is_alnum(char c)
{
	if (is_alpha(c) || (c >= '0' && c <= '9'))
		return 1;
	return 0;
}

char	*ft_strdup(char *s)
{
	int	i;
	char	*ptr;
	if (!s)
		return NULL;
	i = 0;
	while (s[i])
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return ptr;
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

