/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:52:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/27 15:35:04 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
//open, close, read, write, list, free, perror, strerror, access, dup, dup2,
//execve, exit, fork, pipe, unlink, wait, waitpid
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

//error message
# define ERROR_AC "\033[0;31mBad argument\033[0m, please run with 4 or more arguments.\n\
Example : ./pipex infile \"ls -l\" \"wc -l\" outfile."
# define ERROR_MALLOC "\033[0;31mMalloc fail\033[0m"

//for index of pipe fd
enum	e_fd_pipe
{
	READ,
	WRITE,
};

int		ft_error_msg(void);
void	ft_error_msg_exit(void *fd1, void *fd2);
int		ft_check_file(char **av, int ac);
void	ft_free_close_all_fd(int **fd, const int n);

int		ft_exec_first(char *arg, int file_in, int *fd);
int		ft_exec_last(char *arg, int *fd, int file_out);
int		ft_exec(char *arg, int *fd_read, int *fd_write);

#endif