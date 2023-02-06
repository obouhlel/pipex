/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:23:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/06 15:03:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main_exec_here_doc(t_vars *vars)
{
	int		i;

	ft_here_doc(vars);
	i = 0;
	while (i < vars->nb_pipes)
	{
		if (i == 0)
			vars->pid[i] = ft_exec_here_doc(vars, vars->cmds[i], \
			vars->pipes[i][R], vars->pipes[i + 1][W]);
		else if (i == vars->nb_pipes - 1)
			vars->pid[i] = ft_exec_end_here_doc(vars, vars->cmds[i], \
			vars->pipes[i][R], vars->outfile);
		else
			vars->pid[i] = ft_exec(vars, vars->cmds[i], \
			vars->pipes[i][R], vars->pipes[i + 1][W]);
		i++;
	}
	ft_close_pipes(vars);
	if (ft_check_pid(vars->pid, vars->nb_pipes + 1) == FAIL)
		return (ft_error(vars, ERROR_FORK, NULL), FAIL);
	i = -1;
	while (++i < (vars->nb_pipes + 1))
		waitpid(vars->pid[i], NULL, 0);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}

int	ft_exec_here_doc(t_vars *vars, char *arg, int fd_read, int fd_write)
{
	pid_t	id;

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
		ft_execution(vars, arg);
	}
	return (id);
}

int	ft_exec_end_here_doc(t_vars *vars, char *arg, int fd_read, char *file)
{
	int		id;
	int		file_out;

	id = fork();
	if (id == 0)
	{
		if (dup2(fd_read, STDIN) == FAIL)
			return (ft_error_exit(vars, strerror(errno), &ft_close_pipes), \
					FAIL);
		file_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file_out == FAIL)
			return (ft_error(vars, strerror(errno), NULL), FAIL);
		if (dup2(file_out, STDOUT) == FAIL)
			return (close(file_out), \
					ft_error(vars, strerror(errno), &ft_close_pipes), FAIL);
		close(file_out);
		ft_close_pipes(vars);
		ft_execution(vars, arg);
	}
	return (id);
}

void	ft_here_doc(t_vars *vars)
{
	static char	*str = "init";

	while (str)
	{
		ft_putstr_fd("pipe heredoc> ", STDERR);
		str = get_next_line(STDIN);
		if (!str)
			break ;
		if (str && ft_strcmp(str, vars->limiter) == 0)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, vars->pipes[0][W]);
		free(str);
	}
}
