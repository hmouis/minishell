/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:34:53 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/04 14:04:32 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char **cwd, t_var *var)
{
	char	*dir, (*current_dir);

	if (cwd[2])
	{
		dir = cwd[2];
		if (cwd[3] != NULL)
			return (printf("cd: string not in pwd: %s\n", dir), -1);
	}
	else
		return(printf("cd: no directory specified\n"), -1);
	var->oldpwd = getcwd(NULL, 0);
	if (!var->oldpwd)
		return(perror("getwd"), -1);
	if (chdir(dir) == -1)
	{
		printf("cd: no sush file or directory : %s\n", dir);
		return(free(var->oldpwd), -1);
	}
	var->pwd = getcwd(NULL, 0);
	if (!var->pwd)
	{
		perror("getcwd");
		return(free(var->oldpwd), -1);
	}
	printf("old directory : %s\n" , var->oldpwd);
	printf("current directory : %s\n" , var->pwd);
	free(var->oldpwd);
	return(free(var->pwd), 0);
}

