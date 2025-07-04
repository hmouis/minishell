/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:01:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:29:05 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	exec_unset(t_env **env, t_exec **key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	if (!key || !(*key)->args[0] || !(*key)->args[1])
		return ;
	while (curr)
	{
		if (ft_strcmp(curr->key, (*key)->args[1]) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			curr->key = NULL;
			curr->data = NULL;
			curr = NULL;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	g_exit_status = 0;
}
