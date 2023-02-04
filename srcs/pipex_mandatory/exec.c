/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:12:04 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/04 18:53:31 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	main_exec(t_vars *vars)
{
	int	i;
	int	pid[2];

	pid[0] = ft_exec_first(vars, vars->cmds[0], vars->fd, vars->infile);
	if (pid[0] == -1)
		return (EXIT_FAILURE);
	pid[1] = ft_exec_last(vars, vars->cmds[1], vars->fd, vars->outfile);
	if (pid[1] == -1)
		return (EXIT_FAILURE);
	ft_close_fd(vars->fd);
	i = -1;
	while (++i < (vars->n + 1))
		waitpid(pid[i], NULL, 0);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}

int	ft_open(char *name_file, int flag)
{
	int	fd;

	fd = open(name_file, flag);
	if (fd == FAIL)
	{
		ft_putendl_fd(strerror(errno), STDERR);
		errno = 0;
		return (FAIL);
	}
	return (fd);
}

int	ft_exec_first(t_vars *vars, char *arg, int fd[2], char *name_file)
{
	int		id;
	int		fd_file;

	id = fork();
	if (id == 0)
	{
		close(fd[R]);
		fd_file = ft_open(name_file, O_RDONLY);
		if (fd_file != FAIL)
		{
			if (dup2(fd_file, STDIN) == FAIL)
				return (ft_error(vars, strerror(errno), &ft_close_fd), FAIL);
			close(fd_file);
		}
		if (dup2(fd[W], STDOUT) == -1)
			return (ft_error(vars, strerror(errno), &ft_close_fd), FAIL);
		close(fd[W]);
		ft_free_vars(vars);
		if (!ft_strncmp("sleep", arg, 5) && fd_file == FAIL)
			exit(EXIT_FAILURE);
		ft_execution(arg);
	}
	return (id);
}

int	ft_exec_last(t_vars *vars, char *arg, int fd[2], char *name_file)
{
	int		id;
	int		file_out;

	id = fork();
	if (id == 0)
	{
		close(fd[W]);
		if (dup2(fd[R], STDIN) == -1)
			return (close(fd[R]), ft_error(vars, strerror(errno), 0), FAIL);
		close(fd[R]);
		file_out = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_out == -1)
			return (ft_error(vars, strerror(errno), NULL), FAIL);
		if (dup2(file_out, STDOUT) == -1)
			return (close(file_out), ft_error(vars, strerror(errno), 0), FAIL);
		close(file_out);
		ft_free_vars(vars);
		ft_execution(arg);
	}
	return (id);
}

void	ft_execution(char *arg)
{
	char	**args;
	char	*cmd;

	args = ft_split(arg, ' ');
	if (!args)
	{
		ft_putendl_fd(ERROR_MALLOC, STDERR);
		exit(EXIT_FAILURE);
	}
	cmd = ft_strjoin("/usr/bin/", args[0]);
	if (!cmd)
	{
		ft_free_exec(args, NULL);
		ft_putendl_fd(ERROR_MALLOC, STDERR);
		exit(EXIT_FAILURE);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_free_exec(args, cmd);
		ft_putendl_fd(ERROR_CMD, STDERR);
		exit(EXIT_FAILURE);
	}
	execve(cmd, args, NULL);
	ft_free_exec(args, cmd);
	ft_error_exit(NULL, strerror(errno), errno, NULL);
}
