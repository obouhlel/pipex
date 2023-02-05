/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:52:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 12:11:23 by obouhlel         ###   ########.fr       */
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

//return value
# define SUCCESS 0
# define FAIL -1

//error message
# define ERROR_AC "\033[0;31mBad argument\033[0m, please run with 4 or more arguments.\n\
Example : ./pipex infile \"ls -l\" \"wc -l\" outfile."
# define ERROR_ACHD "\033[0;31mBad argument\033[0m, please run with 5 or more arguments.\n\
Example : ./pipex here_doc LIMITER \"cat\" \"grep o\" outfile."
# define ERROR_MALLOC "\033[0;31mMalloc fail\033[0m"
# define ERROR_PATH "\033[0;31mBad path\033[0m, please check your PATH variable."
# define ERROR_CMD "Command not found"

//std fd
# define STDIN	0
# define STDOUT	1
# define STDERR 2

//for index of pipe fd
enum	e_fd_pipe
{
	R,
	W,
};

//vars struct
typedef struct s_vars
{
	int		n;
	char	*infile;
	char	*outfile;
	char	**path;
	char	**cmds;
	int		fd[2];
}	t_vars;

//error.c
void	ft_error_exec(t_vars *vars, char **args, char *tmp, char *msg);
void	ft_error_exit(t_vars *vars, char *msg, int exit_code, void (*f)(int *));
void	ft_error(t_vars *vars, char *msg, void (*f)(int *));

//free.c
void	ft_free_strs(char **strs);
void	ft_free_vars(t_vars *vars);

//utils.c
char	**ft_get_path(char **env);
void	ft_close_fd(int fd[2]);

//vars.c
t_vars	*ft_init_vars(int ac, char **av, char **env);

//exec.c
int		main_exec(t_vars *vars);
int		ft_exec_first(t_vars *vars, char *arg, int fd[2], char *name_file);
int		ft_exec_last(t_vars *vars, char *arg, int fd[2], char *name_file);
void	ft_execution(t_vars *vars, char *arg);

#endif