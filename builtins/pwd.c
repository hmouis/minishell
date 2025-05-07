/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:10:44 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/04 18:20:06 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*builtin_pwd(char **av)
{
	char	*cwd;

	if (av[2] && ft_strcmp(av[2], "-"))
	{
		printf("pwd: too many arguments\n");
		return NULL;
	}
	cwd = getcwd(0, NULL);
	return cwd;
}

