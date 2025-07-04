/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:29:11 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/30 22:28:42 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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
