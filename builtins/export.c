/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:37:47 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/05/09 15:38:22 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	builtin_export(t_env **env, char *s)
{
	t_env *last, *first;
	char	*key, *data, *equals_sign;

	key = get_env_key(s);
	data = get_env_data(s);
	if (!key || !data)
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		free(key); 
		free(data); 
		return;
	}
	if (*env == NULL)
		*env = env_new_node(key, data) ;
	first = *env;
	while (first)
	{
		if (ft_strcmp(first->key, key) == 0)
		{	
			free(first->data);
			first->data = ft_strdup(data);
			free(key);
			return ;
		}
		if (first->next == NULL)
			last = first;
		first = first->next;
	}
	first = *env;
	last->next = env_new_node(key, data);
}
