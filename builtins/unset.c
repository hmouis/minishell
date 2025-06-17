/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:01:01 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/31 22:35:59 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_unset(t_env **env, t_exec **key)
{
	t_env	*tmp;
	t_env	*after_node;

	tmp = *env;
	if (!key || !(*key)->args[0] || !(*key)->args[1])
		return;
	while (tmp)
	{
		if (!tmp)
			return;
		after_node = tmp->next;
		if (ft_strcmp(after_node->key, (*key)->args[1]) == 0)
		{
			tmp->next = after_node->next;
			free(after_node->key);
			free(after_node->data);
		}
		tmp = tmp->next;
	}
	g_exit_status = 0;
}
