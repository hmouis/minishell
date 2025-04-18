/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:42:29 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/04/18 11:48:44 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../minishell.h"*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handle_ctrl_c(int sig)
{
	(void)sig;
	printf("minishell~ \n");
}

void	handle_ctrl_backslash(int sig)
{
	(void)sig;
	return ;
}

int main()
{
	char	*line;

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backslash);
	line = readline("minishell~ ");
	if (line == NULL)
	{
		printf("exit");
		exit(0);
	}
	while (1)
		pause();
	return 0;
}
