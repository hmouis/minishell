/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:06:13 by hmouis            #+#    #+#             */
/*   Updated: 2025/04/17 18:09:32 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*test_line;
	t_lst	*lst;

	lst = NULL;
	while (1)
	{
		test_line = readline("minishell: ");
		add_history(test_line);
		if (!test_line)
			break ;
		split_input(test_line, &lst);
		while (lst)
		{
			tokens_type(&lst);
			printf("token : %s\n", lst->content);
			printf("type : %s\n", lst->type);
			lst = lst->next;
		}
	}
}
