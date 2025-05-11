/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:55:05 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/08 15:11:11 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_env *env)
{
	t_env *first;

	first = env;
	while (first)
	{
		printf("%s=%s\n", first->key, first->data);
		first = first->next;
	}
}
