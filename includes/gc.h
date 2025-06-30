/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:45:18 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 23:02:35 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "./structures.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstdelone_env(t_list_env *lst, void (*del)(void *));
void	*ft_malloc(size_t size, int flag);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstclear_env(t_list_env **lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new_);
char	*ft_strdup_env(char *s);
void	*ft_malloc_env(size_t size, int flag);
char	*ft_substr_env(char *s, int start, int len);

#endif
