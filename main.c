/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:07:22 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/29 17:46:14 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/execution.h"
#include "minishell.h"
#include "./includes/gc.h"

void	empty__line(void)
{
	ft_malloc(0, 0);
	ft_malloc_env(0, 0);
	printf("exit\n");
	exit(g_exit_status);
}

void	read_line(t_final_struct *fnl, t_cmd *cmd, t_env *list, char **env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell~ ");
		change_value(0);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		add_history(line);
		if (!tokenize_input(line, &cmd))
			continue ;
		fnl = fill_fnl(cmd, fnl, list);
		if (cmd && fnl && fnl->herdoc)
			pars_herdoc(fnl, cmd->redirect);
		if (fnl)
			execute(fnl, list, env);
		cmd = NULL;
		fnl = NULL;
		free(line);
	}
}

int		g_exit_status;

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_final_struct	*fnl;
	t_cmd			*cmd;
	t_env			*list;

	line = NULL;
	fnl = NULL;
	cmd = NULL;
	list = NULL;
	add_env_to_list(&list, env);
	(void)ac;
	(void)av;
	read_line(fnl, cmd, list, env);
}
