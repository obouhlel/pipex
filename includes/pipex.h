/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:52:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/30 08:38:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define SUCCESS (void *)1

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
	R,
	W,
};

typedef struct s_vars
{
	int		here_doc;
	int		n;
	char	**cmds;
	int		file_in;
	int		file_out;
	int		**fd;
}	t_vars;

int		ft_error_msg(void);
void	ft_error_msg_exit(void);
int		ft_check_file_out(int ac, char **av);
void	ft_free_close_all_fd(int **fd, const int n);

t_vars	*ft_init_vars(int ac, char **av);
void	ft_free_vars(t_vars *vars);

int		ft_exec_first(t_vars *vars, char *arg, int file_in, int *fd);
int		ft_exec_last(t_vars *vars, char *arg, int *fd, int file_out);
int		ft_exec(t_vars *vars, char *arg, int *fd_read, int *fd_write);

#endif