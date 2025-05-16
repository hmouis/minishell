/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:37:29 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/13 16:42:16 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int ac, char **av, char **env)
{
	char *buff;
	int pid_child = fork();
	int exit_status;
	if (pid_child == 0)
		execve(av[1], &av[1], NULL);
	else 
		wait(&exit_status);
}
