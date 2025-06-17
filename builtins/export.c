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
			current->data = NULL;
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

int	pars_export(char *s)	
{
	int	i;

	i = 0;
	if (s[i] && s[i] == '=')
	{
		if (s[i + 1] && s[i + 1] == ' ')
		{
			ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
			g_exit_status = 1;
			return -1;
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
			return -1;
		}
	}
	return 1;
}

void	exec_export(t_env **env, t_exec **cmd)
{
	int	i;
	char	*equal;
	char	*key, *value;

	i = 1;
	if (!cmd || !cmd[0])
		return;
	while ((*cmd)->args[i])
	{
		char *s = (*cmd)->args[i];
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
			key = s;
			value = NULL;
			if ((*cmd)->args[i + 1] == NULL)
				return;
			if (pars_export((*cmd)->args[i + 1]) == -1)
				return;
		}
		if (!is_valid_env_key(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd((*cmd)->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
			return ;
		}
		if (value)
			add_or_update_env(env, key, value);
		i++;
	}
	g_exit_status = 0;
}

