/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:52:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 21:26:07 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
# define PIPE_FAIL (void *)-1

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

//pipex mode
enum	e_here_doc_status
{
	NORMAL,
	HERE_DOC,
};

//vars struct
typedef struct s_vars
{
	int		nb_pipes;
	int		here_doc;
	char	*limiter;
	char	*infile;
	char	*outfile;
	char	**path;
	char	**cmds;
	int		**pipes;
}	t_vars;

//file error.c
void	ft_error_exec(t_vars *vars, char **args, char *tmp, char *msg);
void	ft_error_exit(t_vars *vars, char *msg, void (*ft_close)(t_vars *));
void	ft_error(t_vars *vars, char *msg, void (*ft_close)(t_vars *));

//file free.c
void	ft_free_pipes(int **pipes, int nb_pipes);
void	ft_free_strs(char **strs);
void	ft_free_vars(t_vars *vars);

//file utils.c
char	*ft_access(char *cmd, char **path);
char	**ft_get_path(char **env);
void	ft_close_pipes(t_vars *vars);

//file vars.c
t_vars	*ft_init_vars(int ac, char **av, char **env);
void	ft_init_vars_bis(t_vars *vars, int ac, char **av);
char	**ft_init_vars_cmds(char **av, int nb_cmds);
int		**ft_init_vars_pipes(t_vars *vars);

//file exec.c
int		main_exec(t_vars *vars);
int		ft_exec_first(t_vars *vars, char *arg, int fd[2], char *name_file);
int		ft_exec(t_vars *vars, char *arg, int fd_read[2], int fd_write[2]);
int		ft_exec_last(t_vars *vars, char *arg, int fd[2], char *name_file);
void	ft_execution(t_vars *vars, char *arg);

//file here_doc.c
int		main_exec_here_doc(t_vars *vars);
int		main_exec_here_doc_bis(t_vars *vars);

#endif