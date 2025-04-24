/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:50:08 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/04/22 14:28:42 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while(s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	is_redirection(t_lst *list, char **opr)
{
	if (!list->content)
		return 0;
	int	i;

	i = 0;
	while (opr[i])
	{
		if (!ft_strcmp(list->content, opr[i]))
			return 1;
		i++;
	}
	return 0;
}

int	is_pipe(t_lst *list)
{
	if (!list->content)
		return 0;
	if (!ft_strcmp(list->content, "|"))
		return 1;
	return 0;
}

void	tokens_type(t_lst **list)
{
	char	*opr[] = {"<<", ">>", ">", "<", NULL};
	if (is_redirection(*list, opr))
		(*list)->type = op_redirection;
	else if (is_pipe(*list))
		(*list)->type = op_pipe;
	else
		(*list)->type = op_word;
}
