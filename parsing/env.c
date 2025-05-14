/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:11:47 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/14 09:43:14 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char *ft_strncpy(char *dest, const char *src, size_t n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return dest;
}

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
		    return (1);
		set++;
	}
	return (0);
}
char	*ft_strchr(char *s, char c)
{
	if (!s)
		return NULL;
	while (*s)
	{
		if (*s == c)
			return s;
		s++;
	}
	if (*s == c)
		return s;
	return NULL;
}

char	*ft_strdup(char *s)
{
	int	i;
	char	*ptr;
	if (!s)
		return NULL;
	i = 0;
	while (s[i])
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return ptr;
}

char	*ft_strtrim(char *s1, const char *set)
{
	int	start, (end), (len);
	char *trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_in_set(s1[end - 1], set))
		end--;
	len = end - start;
	trimmed = (char *)malloc(sizeof(char) * (len + 1));
	if (!trimmed)
		return (NULL);
	strncpy(trimmed, &s1[start], len);
	trimmed[len] = '\0';
	return (trimmed);
}

t_env	*env_new_node(char *key, char *data)
{
	t_env	*node;

	if (!key || !data)
		return NULL;
	node = malloc(sizeof(t_env));
	if (!node)
		return NULL;
	node->key = key;
	node->data = data;
	node->next = NULL;

	return node;
}

char	*get_key_env(char *s)
{
	char *equals_sign;
	char *key;
	int length;

	equals_sign = ft_strchr(s, '=');
	if (!equals_sign)
	{
		equals_sign = ft_strchr(s, ' ');
		length = equals_sign - s; 
	}
	else
		length = equals_sign - s; 
	key = malloc(length + 1);
	if (!key)
		return NULL;
	strncpy(key, s, length);
	key[length] = '\0';
	return ft_strtrim(key, " ");
}

char	*get_data_env(char *s)
{
	char *equals_sign;
	char *data;

	equals_sign = ft_strchr(s, '=');
	if (!equals_sign)
		return ft_strchr(s, ' ');
	data = ft_strdup(equals_sign + 1);
	if (!data)
		return NULL;
	return ft_strtrim(data, " "); 
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
        char *key = get_key_env(env[i]);
        char *data = get_data_env(env[i]);
	if (!key || !data)
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
