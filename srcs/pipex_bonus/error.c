/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 19:02:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_error_exec(t_vars *vars, char **args, char *tmp, char *msg)
{
	close(STDIN);
	close(STDOUT);
	if (vars)
		ft_free_vars(vars);
	if (args)
		ft_free_strs(args);
	if (tmp)
		ft_free((void **)&tmp);
	if (msg)
		ft_putendl_fd(msg, STDERR);
	exit(EXIT_FAILURE);
}

void	ft_error(t_vars *vars, char *msg, void (*ft_close)(t_vars *))
{
	if (msg)
		ft_putendl_fd(msg, STDERR);
	if (ft_close)
		ft_close(vars);
	if (vars)
		ft_free_vars(vars);
}

void	ft_error_exit(t_vars *vars, char *msg, void (*ft_close)(t_vars *))
{
	if (msg)
		ft_putendl_fd(msg, STDERR);
	if (ft_close)
		ft_close(vars);
	if (vars)
		ft_free_vars(vars);
	exit(errno);
}

int	ft_check_pid(pid_t *pid, int nb_pid)
{
	int	i;

	i = 0;
	while (i < nb_pid)
	{
		if (pid[i] == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
