/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:12:04 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 18:29:02 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	main_exec(t_vars *vars)
{
	int	i;
	int	pid[2];

	pid[0] = ft_exec_first(vars, vars->cmds[0], vars->fd, vars->infile);
	if (pid[0] == FAIL)
		return (EXIT_FAILURE);
	pid[1] = ft_exec_last(vars, vars->cmds[1], vars->fd, vars->outfile);
	if (pid[1] == FAIL)
		return (EXIT_FAILURE);
	ft_close_fd(vars->fd);
	i = -1;
	while (++i < (vars->nb_pipes + 1))
		waitpid(pid[i], NULL, 0);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}

int	ft_exec_first(t_vars *vars, char *arg, int fd[2], char *name_file)
{
	int		id;
	int		fd_file;

	id = fork();
	if (id == 0)
	{
		fd_file = open(name_file, O_RDONLY);
		if (fd_file == FAIL)
			return (ft_error(vars, strerror(errno), &ft_close_fd), FAIL);
		if (dup2(fd_file, STDIN) == FAIL)
			return (close(fd_file), \
					ft_error(vars, strerror(errno), &ft_close_fd), FAIL);
		close (fd_file);
		close(fd[R]);
		if (dup2(fd[W], STDOUT) == FAIL)
			return (ft_error(vars, strerror(errno), &ft_close_fd), FAIL);
		close(fd[W]);
		ft_execution(vars, arg);
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
		if (dup2(fd[R], STDIN) == FAIL)
			return (close(fd[R]), ft_error(vars, strerror(errno), 0), FAIL);
		close(fd[R]);
		file_out = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_out == FAIL)
			return (ft_error(vars, strerror(errno), NULL), FAIL);
		if (dup2(file_out, STDOUT) == FAIL)
			return (close(file_out), ft_error(vars, strerror(errno), 0), FAIL);
		close(file_out);
		ft_execution(vars, arg);
	}
	return (id);
}

char	*ft_access(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!tmp)
			return (ft_error(NULL, ERROR_MALLOC, NULL), free(cmd), NULL);
		if (access(tmp, X_OK) != FAIL)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_execution(t_vars *vars, char *arg)
{
	char	**args;
	char	*cmd;
	char	*tmp;

	args = ft_split(arg, ' ');
	if (!args)
		ft_error_exec(vars, NULL, NULL, ERROR_MALLOC);
	tmp = ft_strjoin("/", args[0]);
	if (!tmp)
		ft_error_exec(vars, args, NULL, ERROR_MALLOC);
	cmd = ft_access(tmp, vars->path);
	if (!cmd)
		ft_error_exec(vars, args, tmp, ERROR_CMD);
	free(tmp);
	ft_free_vars(vars);
	execve(cmd, args, NULL);
	ft_error_exec(NULL, args, cmd, strerror(errno));
}
