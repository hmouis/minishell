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

t_env	*env_new_node(char *key, char *data)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return NULL;
	node->key = key;
	node->data = data;
	node->next = NULL;

	return node;
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

void	add_env_to_list(t_env **lst, char **env) 
{
	if (!env || !*env)
		return ;
	int	i;
	t_env	*temp = NULL;
	t_env	*first = NULL;

	first = env_new_node(get_key_env(env[0]), get_data_env(env[0]));
	if (!first)
		return ;
	i = 1;
	temp = first;
	while (env[i])
	{
		temp->next = env_new_node(get_key_env(env[i]), get_data_env(env[i]));
		if (!temp->next)
		    return ; 
		temp = temp->next;
		i++;
	}
	*lst = first;
}

int main(int ac, char **av, char **env)
{
	t_env	*list, *first;

	list = NULL;
	add_env_to_list(&list, env);
	first = list;
	while (first)
	{
		printf("%s\n", first->key);
		first = first->next;
	}
	
	return 0;
}
