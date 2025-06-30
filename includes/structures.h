/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:00:03 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:56:05 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "./libft.h"

typedef struct s_env
{
	char					*key;
	char					*data;
	char					*oldpwd;
	char					*pwd;
	struct s_env			*next;
}							t_env;

// variables for functions
typedef struct s_var_export
{
	int						i;
	char					*equal;
	char					*key;
	char					*s;
	char					*value;
}							t_var_export;

typedef struct s_var_env
{
	int						i;
	char					*key;
	char					*data;
}							t_var_env;

/*type of tokens*/
typedef enum e_types
{
	op_redirect_input,
	op_redirect_output,
	op_herdoc,
	op_append,
	op_pipe,
	word,
	var,
	string,
	single_quote,
	double_quote,
	type_invalid = -1
}							t_types;

typedef enum e_builtins_type
{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit,
}							t_builtins_type;

typedef struct s_list
{
	void					*content;
	struct s_list			*next;
}							t_list;

typedef struct s_list_env
{
	void					*content;
	struct s_list_env		*next;
}							t_list_env;

typedef struct s_lst
{
	char					*content;
	enum e_types			type;
	struct s_lst			*next;
}							t_lst;

typedef struct s_var
{
	int						i;
	int						y;
	char					*token;
	int						length;
}							t_var;

typedef struct s_exp
{
	char					*content;
	t_types					type;
	struct s_exp			*next;
}							t_exp;

typedef struct s_exec
{
	char					**args;
	int						*exit_status;
}							t_exec;

typedef struct s_gnl
{
	char					*str;
	t_types					type;
	struct s_gnl			*next;
}							t_gnl;

typedef struct s_herdoc
{
	t_gnl					*list;
	struct s_herdoc			*next;
}							t_herdoc;

typedef struct s_final_struct
{
	t_gnl					*args;
	t_gnl					*redirect;
	t_herdoc				*herdoc;
	t_env					*lst_env;
	struct s_final_struct	*next;
}							t_final_struct;

typedef struct s_exec_pipe
{
	int						fd[2];
	int						in_fd;
	int						wstatus;
	pid_t					pid;
	pid_t					last_pid;
}							t_exec_pipe;

typedef struct s_apply_red
{
	int						fd;
	int						redirect;
	int						flag;
}							t_apply_red;

typedef struct s_new_exp
{
	t_lst					*string;
	t_types					type;
	struct s_new_exp		*next;
}							t_new_exp;

typedef struct s_cmd
{
	t_lst					*arg;
	char					**args;
	t_lst					*redirect;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_va
{
	int						i;
	int						start;
	int						len;
}							t_va;

typedef struct s_helper_var
{
	char					*str;
	char					*field_str;
	int						flag;
}							t_helper_va;

typedef struct s_h_pars_fnl
{
	int						reminder;
	int						flag;
}							t_v;

typedef struct s_child_params
{
	t_final_struct			*fnl;
	t_exec_pipe				*var;
	t_env					*lst_env;
	char					**env;
}							t_child_params;

typedef struct s_child_var
{
	t_final_struct			*fnl;
	t_exec_pipe				*var;
	t_env					*lst_env;
}							t_child_v;

#endif
