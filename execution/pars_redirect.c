/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:30:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:30:12 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	pars_red(t_gnl *red)
{
	int	count;

	count = 0;
	while (red)
	{
		red = red->next;
		while (red && (red->type == -1 || red->type == var))
		{
			count++;
			if (count > 1)
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				return (0);
			}
			red = red->next;
		}
		count = 0;
	}
	return (1);
}
