/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:03:24 by hmouis            #+#    #+#             */
/*   Updated: 2025/04/18 10:39:48 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_types
{
	op_redirect_input,  // <
	op_redirect_output, // >
	op_herdoc,          // <<
	op_append,          // >>
	op_pipe,            // |
	argument,
	file_name,
	delimiter,
	cmd,
}					t_types;

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	char			*file_name;
	t_types			type;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_lst
{
	char			*content;
	enum e_types	type;
	struct s_lst	*next;
}					t_lst;

typedef struct s_var
{
	int				i;
	int				y;
	char			*token;
	int				length;
}					t_var;

int					ft_strcmp(char *s1, char *s2);
int					token_operator(t_var *var, char *input, t_lst **lst);
int					end_of_input(t_var *var, char *input, t_lst **lst);
int					creat_token(t_var *var, char *input, t_lst **lst);
int					token_blank(t_var *var, char *input, t_lst **lst);
int					valid_operator(char c1, char c2);
int					white_space(char c);
int					is_operator(char *str);
int					charchr(char *str, int c);
char				*ft_strlcpy(char *token, char *input, int len, int j);
t_lst				*last_node(t_lst *lst);
void				add_back(t_lst **lst, t_lst *node);
void				*new_node(char *content);
void				add_to_lst(t_lst **lst, char *content);
int					split_input(char *input, t_lst **lst);
int					token_quote(int *i, char *input, t_lst **lst, t_var *var);
int					token_dollar_sign(int *i, char *input, t_lst **lst,
						t_var *var);
void				tokens_type(t_lst *lst);
#endif
