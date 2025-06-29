/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:34:02 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/29 15:34:53 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_data(char *s)
{
	char	*equal;

	equal = ft_strchr(s, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

char	*get_env(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (env->data);
		env = env->next;
	}
	return (NULL);
}
