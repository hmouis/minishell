/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:00:25 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/01 15:26:42 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numbers(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return 0;
	while (arg[i])
	{
		if (ft_is_digits(arg[i]) == 0)
			return 0;
		i++;
	}
	return 1;
}

void	exec_exit(t_final_struct *fnl, t_exec **cmd)
{
	int i, (status);

	i = 0;
	if ((*cmd)->args[1] && (*cmd)->args[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_exit_status = 1;
		ft_malloc(0, 0);
		return ;
	}
	else if ((*cmd)->args[1] && !is_numbers((*cmd)->args[1]))
	{
		ft_putstr_fd("exit\nminishell: exit : numeric argument required\n", 2);
		g_exit_status = 2;
		exit (2);
	}
	if (!(*cmd)->args[1])
	{
		g_exit_status = 0;
		if (fnl && !fnl->next)
			printf("exit\n");
		ft_malloc(0, 0);
		exit (0);
	}
	g_exit_status = ft_atoi((*cmd)->args[1]) % 256;
	ft_malloc(0, 0);
	printf("exit\n");
	exit(g_exit_status);
}
