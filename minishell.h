/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:05:54 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/01 00:31:48 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./includes/structures.h"

extern int		g_exit_status;

t_herdoc		*fill_herdoc(t_lst *redirect, t_env *env, t_herdoc **herdoc);
int				change_value(int value);

/*syntax errors*/
void			error_msg(char *str, int status);
int				is_quote(char c);
char			*pipe_line(t_lst *lst, int *status);

/*helper functions*/

void			empty__line(void);
int				tokenize_input(char *line, t_cmd **cmd);
void			pars_herdoc(t_final_struct *fnl, t_lst *lst);
void			move_struct(t_final_struct **fnl, t_cmd **cmd,
					t_herdoc *herdoc);
t_final_struct	*fill_fnl(t_cmd *cmd, t_final_struct *fnl, t_env *list);
void			handle_sig(int sig);

/*type of token*/
void			tokens_type(t_lst *lst);
int				is_redirection(t_lst *lst);
int				is_pipe(t_lst *lst);

/*linked list*/
t_cmd			*creat_cmd_struct(t_cmd **cmd, t_lst *lst);
t_cmd			*node(void);
t_lst			*last_node(t_lst *lst);
void			add_back(t_lst **lst, t_lst *node);
void			*new_node(char *content);
void			add_to_lst(t_lst **lst, char *content);

/*get env*/
int				is_builtins(char *cmd);
int				builtin_cd(char **cwd, t_var *var);
int				is_in_set(char c, const char *set);
t_env			*env_new_node(char *key, char *data);
char			*get_env(char *str, t_env *env);
char			*get_env_key(char *s);
char			*get_env_data(char *s);
char			*get_data_env(char *env);
void			add_env_to_list(t_env **lst, char **env);
void			add_env_if_empty(t_env **list);
int				split_char(char c);
int				split_var_arg(char *str, char **field_str);

#endif
