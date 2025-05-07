/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:06:13 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/07 10:57:17 by hmouis           ###   ########.fr       */
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
	t_lst	*lst;
	t_cmd	*cmd;
	char	*err_msg;
	int		i;

	cmd = NULL;
	err_msg = NULL;
	i = 1;
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
		{
			tokens_type(lst);
			err_msg = pipe_line(lst);
			if (err_msg)
			{
				error_msg(err_msg);
				printf("\n");
			}
			else
			{
				cmd = creat_cmd_struct(&cmd, lst);
				while (cmd)
				{
					printf("command number %i : \n", i);
					i++;
					while (cmd->redirect)
					{
						printf("cmd->redirect :  '%s'\n", cmd->redirect->content);
						cmd->redirect = cmd->redirect->next;
					}
					while (cmd->arg)
					{
						printf("cmd->arg : %10s\n", cmd->arg->content);
						cmd->arg = cmd->arg->next;
					}
					cmd = cmd->next;
				}
			}
			while (lst)
			{
				printf("token : %10s <---> ", lst->content);
				enum_type(lst->type);
				lst = lst->next;
			}
		}
			free_all(&lst, &cmd);
			cmd = NULL;
			lst = NULL;
	}
}
