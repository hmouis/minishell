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

void	enum_type(enum e_types tp)
{
	if (tp == 0)
		printf("type : redirect input\n");
	else if (tp == 1)
		printf("type : redirect output\n");
	else if (tp == 2)
		printf("type : herdoc\n");
	else if (tp == 3)
		printf("type : append\n");
	else if (tp == 4)
		printf("type : pipe\n");
	else if (tp == 5)
		printf("type : argument\n");
	else if (tp == 6)
		printf("type : file name\n");
	else if (tp == 7)
		printf("type : delimiter\n");
	else if (tp == 8)
		printf("type : command\n");
}
int	main(void)
{
	char	*test_line;
	t_lst	*lst;

	lst = NULL;
	test_line = NULL;
	while (1)
	{
		test_line = readline("minishell: ");
		add_history(test_line);
		if (!test_line)
			break ;
		split_input(test_line, &lst);
		if (lst)
			tokens_type(lst);
		while (lst)
		{
			printf("token : %s <---> ", lst->content);
			enum_type(lst->type);
			lst = lst->next;
		}
	}
}
