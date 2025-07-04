/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:03:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:28:19 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/tokenization.h"
#include "../minishell.h"

void	print_with_exit_status(const char *arg)
{
	int	i;
	int	in_single_quote;

	i = 0;
	in_single_quote = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			in_single_quote = !in_single_quote;
			putchar(arg[i]);
			i++;
		}
		else
		{
			putchar(arg[i]);
			i++;
		}
	}
}

void	exec_echo(t_exec **cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while ((*cmd)->args[i] && rev_charchr((*cmd)->args[i]))
	{
		newline = 0;
		i++;
	}
	while ((*cmd)->args[i])
	{
		print_with_exit_status((*cmd)->args[i]);
		if ((*cmd)->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	g_exit_status = 0;
}
