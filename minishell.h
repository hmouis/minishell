/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmouis <hmouis@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:03:24 by hmouis            #+#    #+#             */
/*   Updated: 2025/05/21 18:44:09 by hmouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*env*/
typedef struct	s_env
{
	char		*key;
	char		*data;
	struct s_env	*next;
}			t_env;

/*type of tokens*/
typedef enum	e_types
{
	op_redirect_input,  // <
	op_redirect_output,// >
	op_herdoc,        // <<
	op_append,       // >>
	op_pipe,        // |
	word,
	var,
	string,
	single_quote,
	double_quote,
}		t_types;


typedef enum	e_builtins_type
{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit,
}		t_builtins_type;

typedef struct s_lst
{
	char			*content;
	enum e_types		type;
	struct s_lst		*next;
}				t_lst;

typedef struct s_var
{
	int			i;
	int			y;
	char			*token;
	int			length;
}				t_var;

typedef struct s_exp
{
	char 			*content;
	t_types			type;
	struct s_exp		*next;
}				t_exp;

typedef struct s_gnl
{
	char			*str;
	struct s_gnl		*next;
}				t_gnl;

typedef struct	s_exec
{
	char			**args;
}				t_exec;

typedef struct s_final_struct
{
	t_gnl			*args;
	t_gnl			*redirect;
	struct s_final_struct	*next;
}				t_final_struct;

typedef struct s_new_exp
{
	t_lst 			*string;
	struct s_new_exp	*next;
}				t_new_exp;

typedef struct s_cmd
{
	t_lst			*arg;
	char			**args;
	t_lst			*redirect;
	struct s_cmd		*next;
}				t_cmd;

/*new expansion*/
t_final_struct			*creat_new_exp(t_env *list, t_new_exp **exp, t_cmd *cmd, t_final_struct **fnl);
char				*ft_strjoin(char *s1, char *s2);
void				expand(t_new_exp *exp, t_env *env, t_gnl **gnl);

/*expansion*/
char				**ft_split(char *s, char c);
char				*char_join(char *str, int count, char c);
int					is_digit(char c);
int					str_len(char *str);
char				*char_join(char *str, int count, char c);
char				*replace_empty_var(char *str);
void				expand_quote(t_exp **lst, char *str);
char				*expand_var(t_exp *exp, t_env *lst);
void				type_of_var(t_exp *exp);
int					var_char(char c);
t_exp				*new_var_node(char *content);
t_exp				*last_node_var(t_exp *lst);
void				add_var_back(t_exp **lst, t_exp *node);
void				add_to_var_lst(t_exp **lst, char *content);
int					tokenize_dollar_sign(t_exp **exp, char *str);

/*syntax errors*/
void				error_msg(char *str);
char				*check_quote(char *str);
int					is_quote(char c);
char				*pipe_line(t_lst *lst);
char				*simple_command(t_lst **lst);
void				add_to_lst_c(t_lst **lst, t_lst *node);
t_lst				*new_node_c(t_lst *node);

/*helper functions*/
int				valid_operator(char c1, char c2);
int				white_space(char c);
int				is_operator(char *str);
int				charchr(char *str, int c);
char			*ft_strlcpy(char *token, char *input, int len, int j);
t_exec			*gnl_to_array(t_gnl *head);

/*tokenizing*/
int				token_dollar_sign(int *i, char *input, t_lst **lst, t_var *var);
int				split_input(char *input, t_lst **lst);
int				token_quote(int *i, char *input, t_lst **lst, t_var *var);
int				token_operator(t_var *var, char *input, t_lst **lst);
int				end_of_input(t_var *var, char *input, t_lst **lst);
int				creat_token(t_var *var, char *input, t_lst **lst);
int				token_blank(t_var *var, char *input, t_lst **lst);

/*type of token*/
void				tokens_type(t_lst *lst);
int				is_redirection(t_lst *lst);
int				is_pipe(t_lst *lst);

/*linked list*/
t_cmd				*creat_cmd_struct(t_cmd **cmd, t_lst *lst);
t_cmd				*node(t_lst *lst);
t_lst				*last_node(t_lst *lst);
void				add_back(t_lst **lst, t_lst *node);
void				*new_node(char *content);
void				add_to_lst(t_lst **lst, char *content);

/*get env*/
int				is_builtins(char *cmd);
int				builtin_cd(char **cwd, t_var *var);
int				is_in_set(char c, const char *set);
t_env				*env_new_node(char *key, char *data);
char				*get_env(char *str, t_env *env);
char				*get_env_key(char *s);
char				*get_env_data(char *s);
char				*get_data_env(char *env);
void				add_env_to_list(t_env **lst, char **env); 



int				split_char(char c);
int				split_var_arg(char *str, char **field_str);


//libft
char				*ft_strdup(char *s);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int				is_alpha(char c);
int				is_alnum(char c);
int				ft_is_digits(char c);
char				*ft_strchr(char *s, char c);
char				*ft_substr(char *s, int start, int len);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strcat(char *s1, char *s2);
char				*ft_strtok(char *str, char *delim);
int				ft_strcmp(char *s1, char *s2);


//exec
int				exec_builtins(t_env **lst_env, char **cmd);
int				exec_simple_cmd(char **cmd, char *path);
void				exec_env(t_env **lst);
void				exec_echo(char **args);
void				exec_export(t_env **env, char **str);
void				exec_pwd();
#endif
