/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:03:24 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/07 11:05:59 by hmouis           ###   ########.fr       */
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
	op_redirect_output,// >
	op_herdoc,        // <<
	op_append,       // >>
	op_pipe,        // |
	word,
}					t_types;

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

typedef struct s_cmd
{
	t_lst			*arg;
	t_lst			*redirect;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_gc
{
	t_lst **lst;
	t_cmd **cmd;
}			t_gc;

/*syntax errors*/
void				error_msg(char *str);
char				*pipe_line(t_lst *lst);
char				*simple_command(t_lst **lst);

/*helper functions*/
int					ft_strcmp(char *s1, char *s2);
int					valid_operator(char c1, char c2);
int					white_space(char c);
int					is_operator(char *str);
int					charchr(char *str, int c);
char				*ft_strlcpy(char *token, char *input, int len, int j);

/*tokenizing*/
int					token_dollar_sign(int *i, char *input, t_lst **lst, t_var *var);
int					split_input(char *input, t_lst **lst);
int					token_quote(int *i, char *input, t_lst **lst, t_var *var);
int					token_operator(t_var *var, char *input, t_lst **lst);
int					end_of_input(t_var *var, char *input, t_lst **lst);
int					creat_token(t_var *var, char *input, t_lst **lst);
int					token_blank(t_var *var, char *input, t_lst **lst);

/*type of token*/
void				tokens_type(t_lst *lst);
int					is_redirection(t_lst *lst);
int					is_pipe(t_lst *lst);

/*linked list*/
t_cmd				*creat_cmd_struct(t_cmd **cmd, t_lst *lst);
t_cmd				*node(t_lst *lst);
t_lst				*last_node(t_lst *lst);
void				add_back(t_lst **lst, t_lst *node);
void				*new_node(char *content);
void				add_to_lst(t_lst **lst, char *content);

/*Garbage Collector*/
void				free_cmd(t_cmd **cmd);
void				free_lst(t_lst **lst);
void				free_all(t_lst **lst, t_cmd **cmd);

#endif
