/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:19 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 20:44:30 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# define INT_MIN -2147483648
# define INT_MAX 2147483647

//function with mem
void			ft_bzero(void *s, size_t n);

//function with string
size_t			ft_strlen(const char *s);
size_t			ft_strlcat(char *dst, const char *src, size_t size);

//malloc
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char const *s, char c);

//print
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstrnbr_fd(char *s, int n, int fd);

#endif
