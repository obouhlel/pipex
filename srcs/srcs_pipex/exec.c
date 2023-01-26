/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:12:04 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 20:29:08 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_exec_first(char *arg, int fd_write)
{
	int		id;
	char	**args;
	char	*cmd;

	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		if (dup2(fd_write, STDOUT_FILENO) == -1)
			ft_error_msg_exit();
		close(fd_write);
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
	else
		wait(NULL);
	return (EXIT_SUCCESS);
}

int	ft_exec(char *arg, int fd_read, int fd_write)
{
	int		id;
	char	**args;
	char	*cmd;

	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		if (dup2(fd_read, STDIN_FILENO) == -1)
			ft_error_msg_exit();
		if (dup2(fd_write, STDOUT_FILENO) == -1)
			ft_error_msg_exit();
		close(fd_read);
		close(fd_write);
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
	return (EXIT_SUCCESS);
}
