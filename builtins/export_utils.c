/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:29:11 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/29 15:32:19 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	only_export(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("declare -x ");
		printf("%s=%s\n", env->key, env->data);
		env = env->next;
	}
}
