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

void	builtin_export(t_env **env, char **args)
{
	int	i;
	char	*s, (*equal);
	char	*key, (*value);

	i = 0;
	while (args[i])
	{
		s = args[i];
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
			ft_putstr_fd(s, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(key);
			return ;
		}
		if (value)
			add_or_update_env(env, key, value);
		else
		    add_or_update_env(env, key, "");
		free(key);
		if (value) 
			free(value);
		i++;
	}
	t_env	*tmp;
	tmp = *env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->data);
		tmp = tmp->next;
	}
}

