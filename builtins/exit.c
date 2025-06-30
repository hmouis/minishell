/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:56:45 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/29 15:28:08 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numbers(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (!isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_error_msg(char *arg)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_malloc(0, 0);
	ft_malloc_env(0, 0);
	exit(2);
}

static void	exit_with_g(void)
{
	ft_malloc(0, 0);
	ft_malloc_env(0, 0);
	printf("exit\n");
	exit(g_exit_status);
}

void	exec_exit(t_final_struct *fnl, t_exec **cmd)
{
	int	track_of;

	track_of = 0;
	if ((*cmd)->args[1] && !is_numbers((*cmd)->args[1]))
		exit_error_msg((*cmd)->args[1]);
	else if ((*cmd)->args[1] && (*cmd)->args[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (!(*cmd)->args[1])
	{
		if (fnl && !fnl->next)
			printf("exit\n");
		ft_malloc(0, 0);
		ft_malloc_env(0, 0);
		exit(g_exit_status);
	}
	ft_atoi((*cmd)->args[1], &track_of);
	if (track_of)
		exit_error_msg((*cmd)->args[1]);
	g_exit_status = ft_atoi((*cmd)->args[1], &track_of) % 256;
	exit_with_g();
}
