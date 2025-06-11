/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:52:43 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/10 14:24:10 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len_(int n)
{
	size_t	i;

	if (n <= 0)
		i = 1;
	else
		i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_reverse(char *p, int length)
{
	int		i;
	char	swap;

	i = 0;
	while (i < length / 2)
	{
		swap = p[length - i - 1];
		p[length - i - 1] = p[i];
		p[i] = swap;
		i++;
	}
}

static void	ft_charge_array(char *p, int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		p[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	int		len;

	i = 0;
	len = ft_len_(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	p = malloc(sizeof(char) * len + 1);
	if (p == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	if (n < 0)
	{
		p[len - 1] = '-';
		n = n * -1;
	}
	ft_charge_array(p, n);
	p[len] = '\0';
	ft_reverse(p, len);
	return (p);
}
