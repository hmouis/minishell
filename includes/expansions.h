/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:37:29 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:54:25 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "./structures.h"

void			fnl_argm(t_env *list, t_lst *argm, t_new_exp **exp,
					t_final_struct **fnl);
void			fnl_red(t_env *list, t_lst *red, t_new_exp **exp,
					t_final_struct **fnl);
void			split_string(char *str, t_new_exp **exp);
void			check_double_quote(char **str, t_env *env, t_new_exp *exp);
void			split_str(char **str, char *field_str, t_gnl **gnl,
					t_new_exp *exp);
void			is_var(t_new_exp *exp, t_helper_va *va, t_env *env,
					t_gnl **gnl);
void			add_space(char **field_str, int *remainder, int *count);
int				skip_split_char(char *str, int *i, int *remainder, int *check);
void			skip_var_char(char *str, int *i, int *len);
int				dollar_sign_in_quote(char *str, t_va *va, t_new_exp **exp);
char			*fnl_str(t_env *env, t_new_exp *exp);
char			*expand_double_quote(char *str, t_env *env);
t_final_struct	*fnl_node(void);
int				redirect_type(char *str);
int				dollar_sign_string(char *str, t_va *va, t_new_exp **exp);
int				quote_string(char *str, t_va *va, t_new_exp **exp);
int				get_flag_v(char c);
int				get_flag_q(char quote);
void			del_last_str(char *str, t_va *va, t_new_exp **exp);
int				split_char(char c);
void			add_to_string_lst(t_lst **lst, char *content, int flag);
void			*new_node_(char *content, int flag);
t_new_exp		*new_lst_node(int type);
int				str_len(char *str);
void			expand_quote(t_exp **lst, char *str);
char			*expand_var(t_exp *exp, t_env *lst);
void			type_of_var(t_exp *exp);
t_exp			*new_var_node(char *content);
t_exp			*last_node_var(t_exp *lst);
void			add_var_back(t_exp **lst, t_exp *node);
void			add_to_var_lst(t_exp **lst, char *content);
int				tokenize_dollar_sign(t_exp **exp, char *str);
int				check_char(char c);
void			add_to_gnl_lst(t_gnl **lst, char *content, int type);
void			add_gnl_back(t_gnl **lst, t_gnl *node);
t_gnl			*final_node(char *content, int type);
t_gnl			*last_node_gnl(t_gnl *lst);
t_final_struct	*creat_new_exp(t_env *list, t_new_exp **exp, t_cmd *cmd,
					t_final_struct **fnl);
char			*ft_strjoin(char *s1, char *s2);
void			expand(t_new_exp *exp, t_env *env, t_gnl **gnl);
int				is_digit(char c);
char			*char_join(char *str, int count, char c);
int				var_char(char c);
void			exit_status_var(t_va *va, char *str, int *flag, int *reminder);

#endif
