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
		printf("type : word\n");
}
int	main(void)
{
	char	*test_line;
	t_var	*var;

	test_line = NULL;
	while (1)
	{
		test_line = readline("minishell: ");
		add_history(test_line);
		builtin_cd(test_line, var);
	}
}
