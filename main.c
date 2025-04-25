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

void	print_banner()
{
	printf(b
	"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
	"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
	"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"
	"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
	"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
	"\033[0m");
}

void	enum_type(enum e_types tp)
{
	if (tp == 0)
		printf("type : redirect input\n");
	else if (tp == 1)
		printf("type : redirect ouput\n");
	else if (tp == 2)
		printf("type : Left shift\n");
	else if (tp == 3)
		printf("type : Right shift\n");
	else if (tp == 4)
		printf("type : pipe\n");
	else if (tp == 5)
		printf("type : word\n");
}
int	main(void)
{
	char	*test_line;
	t_lst	*lst;

	lst = NULL;
	print_banner();
	while (1)
	{
		test_line = readline(g "↬  minishell: " "\033[0m");
		add_history(test_line);
		if (!test_line)
			break ;
		split_input(test_line, &lst);
		while (lst)
		{
			tokens_type(&lst);
			printf("token : %s -> ", lst->content);
			enum_type(lst->type);
			lst = lst->next;
		}
	}
}
