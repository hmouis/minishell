/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:11:47 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/16 11:37:39 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new_node(char *key, char *data)
{
	t_env	*node;

	if (!key || !data)
		return NULL;
	node = ft_malloc(sizeof(t_env), 1);
	if (!node)
		return NULL;
	node->key = key;
	node->data = data;
	node->next = NULL;

	return node;
}

int	invalid_key_or_data(char *key, char *data, t_env *first)
{
	if (!key || !data)
	{
		while (first)
		{
			free(first->key);
			free(first->data);
			free(first);
		}
	    return 0;
	}
	return 1;
}

char	*get_env_key(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '=' || ft_is_digits(s[0]))
	{
		ft_putstr_fd("minishell: export `" , 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(" : not a valid identifier\n", 2);
		return NULL;
	}
	while (s[i] && s[i] != '=')
	{
		if (!is_alnum(s[i]) && s[i] != '_')
		  return NULL;
		i++;
	}
	return ft_substr(s, 0, i);
}

char	*get_env_data(char *s)
{
	char	*equal;

	equal = ft_strchr(s, '=');
	if (!equal)
		return NULL;
	return ft_strdup(equal + 1);
}

char *get_env(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (env->data);
		env = env->next;
	}
	return (NULL);
}

void	add_env_to_list(t_env **lst, char **env) 
{
	if (!env || !*env)
		return ;
	int	i;
	t_env	*temp = NULL;
	t_env	*first = NULL;

	i = 1;
	first = env_new_node(get_env_key(env[0]), get_env_data(env[0]));
	if (!first)
		return ;
	temp = first;
	while (env[i])
	{
		char *key = get_env_key(env[i]);
		char *data = get_env_data(env[i]);
		if (invalid_key_or_data(key, data, first) == 0)
			return ;
		temp->next = env_new_node(key, data);
		if (!temp->next)
		{
			while (first)
			{
				temp = first->next;
				free(first->key);
				free(first->data);
				free(first);
				first = temp;
			}
			return;
		}
		temp = temp->next;
		i++;
	}
	*lst = first;
}

int	is_valid_env_key(const char *s)
{
	int i = 0;
	if (!s || s[0] == '=' || ft_is_digits(s[0]))
		return 0;
	while (s[i] && s[i] != '=')
	{
		if (!is_alnum(s[i]) && s[i] != '_')
			return 0;
		i++;
	}
	return (i != 0);
}

void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;	
	t_env *last = NULL;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->data);
			current->data = ft_strdup(value);
			return;
		}
		last = current;
		current = current->next;
	}
	new_node = env_new_node(ft_strdup(key), ft_strdup(value));
	if (last)
		last->next = new_node;
	else
		*env = new_node;
}

void	exec_export(t_env **env, char **str)
{
	int	i;
	char	*equal;
	char	*key, *value;

	i = 0;
	 if (!*str)
	{
		t_env	*test = *env;
		while (test)
		{
			printf("declare -x %s", (test)->key);
			if ((test)->data && ft_strcmp(test->data, ""))
				printf("=%s\n", (test)->data);
			else
				printf("\n");
			test = test->next;
		}
		return ;
	}
	while (str[i])
	{
		char *s = str[i];
		if (!s)
			return;
		equal = ft_strchr(s, '=');
		if (equal)
		{
			key = ft_substr(s, 0, equal - s);
			value = ft_strdup(equal + 1);
		}
		else
		{
			key = ft_strdup(s);
			value = NULL;
		}
		if (!is_valid_env_key(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(key);
			return ;
		}
		if (value)
			add_or_update_env(env, key, value);
		else
			add_or_update_env(env, key, "");
		free(key);
		i++;
	}
	if (value) 
		free(value);
}

