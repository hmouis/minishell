/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:01:46 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:53:03 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./structures.h"

extern int	g_exit_status;

int			exec_cmd(char **env, t_exec **cmd, t_env *lst_env);
t_exec		*gnl_to_array(t_gnl *head);
char		*file_path(t_env *env, char *file);
void		child_process(t_child_params *params, t_exec **exec);
void		execute(t_final_struct *list, t_env *lst_env, char **env);
void		update_env(t_env **env, char *oldpwd, char *pwd);
void		split_handle_herdoc(int fd2, t_herdoc *herdoc);
void		assigned_var(t_final_struct *tmp, char **file, t_apply_red *vars);
int			apply_redirect(t_final_struct *tmp, int *input_redirected,
				int *output_redirected);
int			exec_invalid_pipe_redirect(t_final_struct *list, t_env *lst_env,
				t_exec_pipe **var);
void		run_in_child(t_child_params *params, t_exec **exec);
void		setup_pipes_and_fork(t_final_struct *list, t_exec_pipe *var,
				t_child_params *params, t_exec *exec);
void		handle_signal_exit(int wstatus, int pid, int last_pid);
void		wait_for_children(int pid, int last_pid, int wstatus);
void		initialize_fds(int *in_fd, int *out_fd);
int			pars_red(t_gnl *red);

#endif
