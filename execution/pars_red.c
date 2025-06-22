/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:42:29 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/22 11:19:26 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	pars_red(t_gnl *red)
{
	int	count;

	count = 0;
	while (red)
	{
		if (red->type == op_herdoc)
		{
			red = red->next;
			while (red && red->type == -1)
				red = red->next;
			continue;		
		} 
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
