/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:55:52 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/01 00:18:47 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include ".//structures.h"

int		token_dollar_sign(int *i, char *input, t_var *var);
int		split_input(char *input, t_lst **lst);
int		token_quote(int *i, char *input, t_var *var);
int		token_operator(t_var *var, char *input, t_lst **lst);
int		end_of_input(t_var *var, char *input, t_lst **lst);
int		creat_token(t_var *var, char *input, t_lst **lst);
int		token_blank(t_var *var, char *input, t_lst **lst);
int		token_dollar_sign(int *i, char *input, t_var *var);
int		split_input(char *input, t_lst **lst);
int		token_quote(int *i, char *input, t_var *var);
int		token_operator(t_var *var, char *input, t_lst **lst);
int		end_of_input(t_var *var, char *input, t_lst **lst);
int		creat_token(t_var *var, char *input, t_lst **lst);
int		token_blank(t_var *var, char *input, t_lst **lst);
int		is_operator(char *str);
int		valid_operator(char c1, char c2);
int		rev_charchr(char *str);
int		charchr(char *str, int c);
int		white_space(char c);
void	add_back(t_lst **lst, t_lst *node);

#endif
