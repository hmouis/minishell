/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:23:53 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:29:00 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	exec_pwd(t_env **env)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		if ((*env)->pwd)
			printf("%s\n", (*env)->pwd);
		else
		{
			perror("pwd");
			g_exit_status = 1;
		}
	}
	else
		printf("%s\n", buffer);
	free(buffer);
	g_exit_status = 0;
}
