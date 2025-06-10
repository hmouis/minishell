/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:12:35 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/10 12:57:50 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable(char **env, t_exec *exec, t_env **lst)
{
	if (!env || !*env || !exec || !lst || !*lst)
		return ;
	int	i;

	i = 0;
	while (exec->args[i])
	{
		if (ft_strcmp(exec->args[i], "$?") == 0)
		{
			(*lst)->key = "?";
			(*lst)->data = ft_itoa(*exec->exit_status);
			add_env_to_list(lst, env);
		}
		i++;
	}
}
