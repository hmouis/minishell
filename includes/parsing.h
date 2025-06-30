/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:08:09 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/01 00:22:43 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./execution.h"
# include "./structures.h"

int			add_inside_quote(char *str, char **new_str, int *i);
int			expand_in_herdoc(t_va *va, char *str, char **new_str, t_env *env);
char		*expand_herdoc(char *str, t_env *env);
void		put_error_msg(char *str);
t_herdoc	*new_herdoc(void);
char		*remove_quotes(char *str);
t_gnl		*empty_line(char *line, t_gnl *lst, char *del);
void		fill_lst(char *line, int flag, t_env *env, t_gnl **lst);
int			ft_getc(FILE *stream);
t_herdoc	*fill_herdoc(t_lst *redirect, t_env *env, t_herdoc **herdoc);
void		error_msg(char *str, int status);
int			is_quote(char c);
int			change_value(int value);
void		handle_sig_herdoc(int sig);
t_gnl		*her_doc(char *del, t_env *env, t_gnl *lst);
char		*check_quote(char *str);
t_lst		*new_node_c(t_lst *node);
void		add_to_lst_c(t_lst **lst, t_lst *node);
void		add_tolst(t_lst **lst, t_cmd **cmd);
t_cmd		*creat_cmd_struct(t_cmd **cmd, t_lst *lst);
char		*n_of_herdoc(t_lst *lst, int *status);
char		*pipe_line(t_lst *lst, int *status);
char		*simple_command(t_lst **lst);
void		allocate_herdoc(int *remainder, t_herdoc **herdoc);
t_cmd		*node(void);

#endif
