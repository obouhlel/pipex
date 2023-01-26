/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:12:04 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 13:49:15 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_exec_first(t_list *list, int id, int fd_write)
{
	char	**argv;
	char	*cmd;

	id = fork();
	if (id == -1)
	{
		close(fd_write);
		ft_free_all(list);
		ft_error_msg_exit();
	}
	if (id == 0)
	{
		if (dup2(fd_write, STDOUT_FILENO) == -1)
		{
			close(fd_write);
			ft_free_all(list);
			ft_error_msg_exit();
		}
		close(fd_write);
		argv = ft_split(list->cmd, ' ');
		if (!argv)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		list->strs = argv;
		cmd = ft_strjoin("/usr/bin/", argv[0]);
		if (!cmd)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		if (access(cmd, R_OK) == -1)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		execve(cmd, argv, NULL);
		ft_error_msg_exit();
	}
}

void	ft_exec_last(t_list *list, int id, int fd_read, int file_out)
{
	char	**argv;
	char	*cmd;

	id = fork();
	if (id == -1)
	{
		close(fd_read);
		close(file_out);
		ft_free_all(list);
		ft_error_msg_exit();
	}
	if (id == 0)
	{
		if (dup2(fd_read, STDIN_FILENO) == -1)
		{
			close(fd_read);
			close(file_out);
			ft_free_all(list);
			ft_error_msg_exit();
		}
		if (dup2(file_out, STDOUT_FILENO) == -1)
		{
			close(fd_read);
			close(file_out);
			ft_free_all(list);
			ft_error_msg_exit();
		}
		close(fd_read);
		close(file_out);
		argv = ft_split(list->cmd, ' ');
		if (!argv)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		list->strs = argv;
		cmd = ft_strjoin("/usr/bin/", argv[0]);
		if (!cmd)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		if (access(cmd, R_OK) == -1)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		execve(cmd, argv, NULL);
		ft_error_msg_exit();
	}
}

void	ft_exec(t_list *list, int id, int fd_read, int fd_write)
{
	char	**argv;
	char	*cmd;

	id = fork();
	if (id == -1)
	{
		close(fd_read);
		close(fd_write);
		ft_free_all(list);
		ft_error_msg_exit();
	}
	if (id == 0)
	{
		if (dup2(fd_read, STDIN_FILENO) == -1)
		{
			close(fd_read);
			close(fd_write);
			ft_free_all(list);
			ft_error_msg_exit();
		}
		if (dup2(fd_write, STDOUT_FILENO) == -1)
		{
			close(fd_read);
			close(fd_write);
			ft_free_all(list);
			ft_error_msg_exit();
		}
		close(fd_read);
		close(fd_write);
		argv = ft_split(list->cmd, ' ');
		if (!argv)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		list->strs = argv;
		cmd = ft_strjoin("/usr/bin/", argv[0]);
		if (!cmd)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		if (access(cmd, R_OK) == -1)
		{
			ft_free_all(list);
			ft_error_msg_exit();
		}
		execve(cmd, argv, NULL);
		ft_error_msg_exit();
	}
}
