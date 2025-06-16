/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 06:40:56 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/26 09:40:19 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_echo(t_exec **cmd)
{
	int	newline;
	int	i;

	i = 1;
	newline = 1;
	if ((*cmd)->args[i] && ft_strcmp((*cmd)->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while ((*cmd)->args[i])
	{
		if (ft_strcmp((*cmd)->args[i], "$?") != 0)
			printf("%s", (*cmd)->args[i]);
		else
			printf("%d", g_exit_status);
		if ((*cmd)->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
