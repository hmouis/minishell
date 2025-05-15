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
#include <stdio.h>

int	exec_simple_cmd(char **cmd)
{
	if (!cmd || !*cmd)
		return -1;
	if (execve(cmd[1], &cmd[1], NULL) == -1)
	{
		perror("Error:");
		return -1;
	}
	return 0;
}

int main(int ac, char **av)
{
	if (ac < 2)
		return -1;
	exec_simple_cmd(av);
}
