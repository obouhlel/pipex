/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:12:04 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 19:13:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main_exec(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < (vars->nb_pipes + 1))
	{
		if (i == 0)
			vars->pid[i] = ft_exec_first(vars, vars->cmds[i], \
			vars->pipes[i][W], vars->infile);
		else if (i == vars->nb_pipes)
			vars->pid[i] = ft_exec_last(vars, vars->cmds[i], \
			vars->pipes[i - 1][R], vars->outfile);
		else
			vars->pid[i] = ft_exec(vars, vars->cmds[i], \
			vars->pipes[i - 1][R], vars->pipes[i][W]);
		i++;
	}
	ft_close_pipes(vars);
	if (ft_check_pid(vars->pid, vars->nb_pipes + 1) == FAIL)
		return (ft_error(vars, ERROR_FORK, ft_close_pipes), FAIL);
	i = -1;
	while (++i < (vars->nb_pipes + 1))
		waitpid(vars->pid[i], NULL, 0);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}

int	ft_exec_first(t_vars *vars, char *arg, int fd_write, char *name_file)
{
	pid_t	id;
	int		fd_file;

	id = fork();
	if (id == 0)
	{
		fd_file = open(name_file, O_RDONLY);
		if (fd_file == FAIL)
			return (ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		if (dup2(fd_file, STDIN) == FAIL)
			return (close(fd_file), \
					ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		close (fd_file);
		if (dup2(fd_write, STDOUT) == FAIL)
			return (ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		ft_close_pipes(vars);
		if (ft_strcmp(arg, "") == 0)
			return (ft_error_exit(vars, ERROR_CMD, NULL), FAIL);
		ft_execution(vars, arg);
	}
	return (id);
}

int	ft_exec(t_vars *vars, char *arg, int fd_read, int fd_write)
{
	int		id;

	id = fork();
	if (id == 0)
	{
		if (dup2(fd_read, STDIN) == FAIL)
			return (ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		if (dup2(fd_write, STDOUT) == FAIL)
			return (ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		ft_close_pipes(vars);
		if (ft_strcmp(arg, "") == 0)
			return (ft_error_exit(vars, ERROR_CMD, NULL), FAIL);
		ft_execution(vars, arg);
	}
	return (id);
}

int	ft_exec_last(t_vars *vars, char *arg, int fd_read, char *name_file)
{
	int		id;
	int		file_out;

	id = fork();
	if (id == 0)
	{
		if (dup2(fd_read, STDIN) == FAIL)
			return (ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		file_out = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_out == FAIL)
			return (ft_error_exit(vars, strerror(errno), NULL), FAIL);
		if (dup2(file_out, STDOUT) == FAIL)
			return (close(file_out), \
					ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		close(file_out);
		ft_close_pipes(vars);
		if (ft_strcmp(arg, "") == 0)
			return (ft_error_exit(vars, ERROR_CMD, NULL), FAIL);
		ft_execution(vars, arg);
	}
	return (id);
}

void	ft_execution(t_vars *vars, char *arg)
{
	char		**args;
	char		*cmd;
	static char	*tmp = NULL;

	args = ft_split(arg, ' ');
	if (!args)
		ft_error_exec(vars, NULL, NULL, ERROR_MALLOC);
	if (access(args[0], X_OK) == FAIL)
	{
		tmp = ft_strjoin("/", args[0]);
		if (!tmp)
			ft_error_exec(vars, args, NULL, ERROR_MALLOC);
		cmd = ft_access(tmp, vars->path);
		if (!cmd)
			ft_error_exec(vars, args, tmp, ERROR_CMD);
	}
	else
	{
		cmd = args[0];
		if (!cmd)
			ft_error_exec(vars, args, NULL, ERROR_MALLOC);
	}
	ft_free_vars_and_tmp(vars, tmp);
	execve(cmd, args, NULL);
	ft_error_exec(NULL, args, cmd, strerror(errno));
}
