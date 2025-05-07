/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:10:57 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/07 18:41:50 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	if (!s)
		return -1;
	while (s[i])
		i++;
	return i;
}

char	*get_key_env(char *env)
{
	int	i;
	char	*key;

	i = 0;
	if (!env)
		return NULL;
	while (env[i] && env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return NULL;
	i = 0;
	while (env[i] && env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return key;
}

char	*get_data_env(char *env)
{
	int	i, (j), (length);
	char	*data;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	length = ft_strlen(env + i);
	data = malloc(sizeof(char) * (length + 1));
	while (env[i + j])
	{
		data[j] = env[i + j];
		j++;
	}
	data[j] = '\0';
	return data;
}

