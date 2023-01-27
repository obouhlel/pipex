/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:12:04 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/27 12:39:14 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	ft_execution(char *arg);

int	ft_exec_first(char *arg, int *fd)
{
	int		id;

	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		close(fd[READ]);
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			ft_error_msg_exit();
		close(fd[WRITE]);
		ft_execution(arg);
	}
	else
		wait(NULL);
	return (EXIT_SUCCESS);
}

int	ft_exec_last(char *arg, int *fd, int file_out)
{
	int		id;

	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		close(fd[WRITE]);
		if (dup2(fd[READ], STDIN_FILENO) == -1)
			ft_error_msg_exit();
		if (dup2(file_out, STDOUT_FILENO) == -1)
			ft_error_msg_exit();
		close(fd[WRITE]);
		close(file_out);
		ft_execution(arg);
	}
	return (EXIT_SUCCESS);
}

int	ft_exec(char *arg, int *fd_read, int *fd_write)
{
	int		id;

	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		close(fd_read[WRITE]);
		close(fd_write[READ]);
		if (dup2(fd_read[READ], STDIN_FILENO) == -1)
			ft_error_msg_exit();
		if (dup2(fd_write[WRITE], STDOUT_FILENO) == -1)
			ft_error_msg_exit();
		close(fd_read[READ]);
		close(fd_write[WRITE]);
		ft_execution(arg);
	}
	return (EXIT_SUCCESS);
}

static void	ft_execution(char *arg)
{
	char	**args;
	char	*cmd;

	args = ft_split(arg, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	cmd = ft_strjoin("/usr/bin/", args[0]);
	if (!cmd)
		exit(EXIT_FAILURE);
	if (access(cmd, X_OK) == -1)
		ft_error_msg_exit();
	execve(cmd, args, NULL);
	ft_error_msg_exit();
}
