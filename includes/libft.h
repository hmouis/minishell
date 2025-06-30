/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:24:50 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/01 00:19:38 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "./headers.h"

char		*ft_strdup(char *s);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			is_alpha(char c);
int			is_alnum(char c);
int			ft_is_digits(char c);
long long	ft_atoi(char *str, int *track_of);
char		*ft_strchr(char *s, char c);
char		*ft_substr(char *s, int start, int len);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strcat(char *s1, char *s2);
char		*ft_strtok(char *str, char *delim);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);
char		*ft_strlcpy(char *token, char *input, int len, int j);

#endif
