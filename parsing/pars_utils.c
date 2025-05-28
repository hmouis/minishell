/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:37:06 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/06 09:38:59 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *str, int status)
{
	if (status == 0)
		printf("bash: syntax error near unexpected token `%s'", str);
	else
		printf("%s",str);
}

t_cmd	*node()
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->arg = NULL;
	cmd->args = NULL;
	cmd->redirect = NULL;
	cmd->next = NULL;
	return (cmd);
}

int is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
