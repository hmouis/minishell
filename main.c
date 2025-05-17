/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:06:13 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/16 11:41:26 by hmouis           ###   ########.fr       */
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
	else if (tp == 6)
		printf("type : var\n");
	else if (tp == 7)
		printf("type : string\n");
}
int	main(int ac, char **av, char **env)
{
	char	*test_line;
	t_lst	*lst;
	t_cmd	*cmd;
	t_cmd	*head;
	char	*err_msg;
	int		i;
	t_exp *exp;
	t_env	*list;

	cmd = NULL;
	exp = NULL;
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
		/*while (lst)*/
		/*{*/
		/*	printf("token : %10s \n", lst->content);*/
		/*	lst = lst->next;*/
		/*}*/
		/*continue;*/
		if (lst)
		{
			tokens_type(lst);
			err_msg = pipe_line(lst);
			if (err_msg)
			{
				error_msg(err_msg);
				printf("\n");
				lst = NULL;
				continue;
			}
			else
			{
				cmd = creat_cmd_struct(&cmd, lst);
				/*while (cmd)*/
				/*{*/
				/*	printf("----------------\n");*/
				/*	while (cmd->redirect)*/
				/*	{*/
				/*		printf("cmd->redirect :  '%s'\n", cmd->redirect->content);*/
				/*	//	enum_type(cmd->redirect->type);*/
				/*		cmd->redirect = cmd->redirect->next;*/
				/*	}*/
				/*	while (cmd->arg)*/
				/*	{*/
				/*		printf("cmd->arg : %10s\n", cmd->arg->content);*/
				/*	//	enum_type(cmd->arg->type);*/
				/*		cmd->arg = cmd->arg->next;*/
				/*	}*/
				/*	cmd = cmd->next;*/
				/*}*/
			}
			/*while (lst)*/
			/*{*/
			/*	printf("token : %10s \n", lst->content);*/
			/*	lst = lst->next;*/
			/*}*/
		}
		head = cmd;
		add_env_to_list(&list, env);
		/*while (list)*/
		/*{*/
		/*	printf("\nkey : %s\n", list->key);*/
		/*	printf("data : %s\n\n", list->data);*/
		/*	list = list->next;*/
		/*}*/
		builtin_export(&list, "aaa=\"a       b        \"");
		while (cmd)
		{
			while (cmd && cmd->arg)
			{
				if (cmd->arg->type == word && charchr(cmd->arg->content ,'$'))
				{
					if (!tokenize_dollar_sign(&exp, cmd->arg->content))
					{
						printf("bash: syntax error: unexpected end of file\n");
						break;
					}
					type_of_var(exp);
					cmd->arg->content[0] = '\0';
					cmd->arg->content = expand_var(exp, list);
					/*while (exp)*/
					/*{*/
					/*		printf("string = %s\n", exp->content);*/
					/*	exp = exp->next;*/
					/*}*/
				}
				else if (charchr(cmd->arg->content, '\'') || charchr(cmd->arg->content, '"'))
					remove_quote(&cmd, 1);
				printf("new string : %s\n", cmd->arg->content);
				exp = NULL;
				cmd->arg = cmd->arg->next;
			}
			cmd = cmd->next;
		}
		exp = NULL;
		cmd = NULL;
		lst = NULL;
	}
}
