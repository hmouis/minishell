/* ************************************************************************** */
/*                                                                            */
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

void	exec_exit(t_exec **cmd)
{
	int i, (status);

	i = 0;
	if ((*cmd)->args[1] && (*cmd)->args[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		status = 2;
		ft_malloc(0, 0);
		exit (2);
	}
	else if ((*cmd)->args[1] && !is_numbers((*cmd)->args[1]))
	{
		ft_putstr_fd("exit\nminishell: exit : numeric argument required\n", 2);
		status = 2;
		(*cmd)->exit_status = &status;
		exit (2);
	}
	if (!(*cmd)->args[1])
	{
		status = 0;
		(*cmd)->exit_status = &status;
		printf("exit\n");
		ft_malloc(0, 0);
		exit (0);
	}
	status = ft_atoi((*cmd)->args[1]);
	(*cmd)->exit_status = &status;
	ft_malloc(0, 0);
	exit(status);
}
