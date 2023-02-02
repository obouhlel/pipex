/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:12:04 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 19:28:42 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	ft_execution(char *arg);

int	ft_exec_first(t_vars *vars, char *arg, int file_in, int fd[2])
{
	int		id;

	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		close(fd[R]);
		if (file_in != -1 && file_in != STDIN_FILENO)
		{
			if (dup2(file_in, STDIN_FILENO) == -1)
				return (ft_free_vars(vars), ft_error_msg_exit(), errno);
			close(file_in);
		}
		if (dup2(fd[W], STDOUT_FILENO) == -1)
			return (ft_free_vars(vars), ft_error_msg_exit(), errno);
		close(fd[W]);
		ft_free_vars(vars);
		ft_execution(arg);
		ft_error_msg_exit();
	}
	return (id);
}

int	ft_exec_last(t_vars *vars, char *arg, int fd[2], int file_out)
{
	int		id;

	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		close(fd[W]);
		if (dup2(fd[R], STDIN_FILENO) == -1)
			return (ft_free_vars(vars), ft_error_msg_exit(), errno);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			return (ft_free_vars(vars), ft_error_msg_exit(), errno);
		close(file_out);
		close(fd[R]);
		ft_free_vars(vars);
		ft_execution(arg);
		ft_error_msg_exit();
	}
	return (id);
}

static void	ft_execution(char *arg)
{
	char	**args;
	char	*cmd;

	args = ft_split(arg, ' ');
	if (!args)
	{
		ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	cmd = ft_strjoin("/usr/bin/", args[0]);
	if (!cmd)
	{
		ft_error_exec(args, NULL);
		ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_error_exec(args, cmd);
		ft_error_msg_exit();
	}
	execve(cmd, args, NULL);
	ft_error_exec(args, cmd);
}
