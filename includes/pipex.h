/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:52:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 11:53:25 by obouhlel         ###   ########.fr       */
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

//list list
typedef struct s_list
{
	int		n;
	char	*cmd;
	int		*id;
	int		**fd;
	char	**strs;
}	t_list;

//for index of pipe fd
enum	e_fd_pipe
{
	READ,
	WRITE,
};

int		ft_error_msg(void);
void	ft_error_msg_exit(void);
void	ft_free_id_fd(int *id, int **fd, int n);
void	ft_free_all(t_list *list);
void	ft_close_all(int **fd, int n);
int		ft_check_file(char **av, int ac);

void	ft_exec_first(t_list *list, int id, int fd_write);
void	ft_exec_last(t_list *list, int id, int fd_read, int file_out);
void	ft_exec(t_list *list, int id, int fd_read, int fd_write);

#endif