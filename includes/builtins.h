/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:09:19 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 23:46:35 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./execution.h"
# include "./expansions.h"
# include "./gc.h"
# include "./headers.h"
# include "./libft.h"
# include "./structures.h"

void	exec_cd(t_env **env, t_exec **cmd);
void	exec_env(t_env **lst);
void	exec_pwd(t_env **env);
void	exec_echo(t_exec **cmd);
void	exec_exit(t_final_struct *fnl, t_exec **cmd);
void	exec_unset(t_env **env, t_exec **key);
void	exec_export(t_env **env, t_exec **cmd);
int		is_builtins(char *cmd);
int		exec_builtins(t_env **lst_env, t_exec **cmd, t_final_struct *struc);
void	only_export(t_env *env);
void	add_or_update_env(t_env **env, char *key, char *value);

#endif
