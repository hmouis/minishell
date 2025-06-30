/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_or_update_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:00:51 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:27:55 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../minishell.h"

void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*cur;
	t_env	*new_node;
	t_env	*last;

	last = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			cur->data = NULL;
			cur->data = ft_strdup(value);
			return ;
		}
		last = cur;
		cur = cur->next;
	}
	new_node = env_new_node(ft_strdup(key), ft_strdup(value));
	if (last)
		last->next = new_node;
	else
		*env = new_node;
}
