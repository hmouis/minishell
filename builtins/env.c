/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:55:05 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:28:24 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	exec_env(t_env **lst)
{
	t_env	*first;

	first = *lst;
	while (first)
	{
		printf("%s=%s\n", first->key, first->data);
		first = first->next;
	}
	g_exit_status = 0;
}
