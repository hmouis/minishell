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

void	error_msg(char *str)
{
	printf("bash: syntax error near unexpected token `%s'", str);
}

t_cmd	*node(t_lst *lst)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = NULL;
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
