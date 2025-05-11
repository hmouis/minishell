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

int	parsing_key(char *key)
{
	int	i;

	if (!key || !key[0] || (!is_alpha(key[0]) && key[0] != '_' ))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	i = 1;
	while (key[i])
	{
		if (!is_alnum(key[i]) && key[i] != '_')
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return 1;
}

int	parsing_data(char *data)
{
	if (!data)
		return 0;
	return 1;
}

void	builtin_export(t_env **env, char *s)
{
	t_env *last, *first, *current;
	char	*key, *data, *equals_sign;

	equals_sign = ft_strchr(s, '=');
	if (equals_sign && (equals_sign > s && equals_sign[-1] == ' '))
	{
		ft_putstr_fd("bash: export: `=': not a valid identifier\n", 2);
		return;
	}
	if (equals_sign && equals_sign[1] == ' ')
	{
		ft_putstr_fd("bash: export: `=': not a valid identifier\n", 2);
		return;
	}
	if (equals_sign)
	{
		if (equals_sign > s && equals_sign[-1] == ' ')
		{
		    ft_putstr_fd("export: `=': not a valid identifier\n", 2);
		    return;
		}

		if (equals_sign[1] == ' ')
		{
		    ft_putstr_fd("export: `", 2);
		    ft_putstr_fd(equals_sign + 1, 2);
		    ft_putstr_fd("': not a valid identifier\n", 2);
		    return;
		}
	}
	key = get_key_env(s);
	data = get_data_env(s);
	if (!key || !data)
	{
		ft_putstr_fd("export: error parsing input\n", 2);
		free(key); 
		free(data); 
		return;
	}
	if (!parsing_key(key))
		return (free(key));
	if (*env == NULL)
		*env = env_new_node(key, data) ;
	first = *env;
	while (first)
	{
		if (ft_strcmp(first->key, key) == 0)
		{	
			free(first->data);
			first->data = ft_strdup(data);
			first->data = data;
			free(key);
			return ;
		}
		if (first->next == NULL)
			last = first;
		first = first->next;
	}
	first = *env;
	last->next = env_new_node(key, data);
	while (first)
	{
		printf("%s=%s\n", first->key, first->data);
		first = first->next;
	}
}

