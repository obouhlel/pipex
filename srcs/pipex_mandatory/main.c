/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 19:13:57 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include <stdio.h>

static int	main_exec(t_vars *vars);

int	main(int ac, char **av)
{
	t_vars	*vars;

	vars = NULL;
	if (ac != 5)
		return (ft_putendl_fd(ERROR_AC, STDERR_FILENO), EXIT_FAILURE);
	vars = ft_init_vars(ac, av);
	if (!vars)
		return (EXIT_FAILURE);
	if (main_exec(vars))
		return (errno);
	return (EXIT_SUCCESS);
}

static int	main_exec(t_vars *vars)
{
	// int	i;
	int	pid[2];

	pid[0] = ft_exec_first(vars, vars->cmds[0], vars->file_in, vars->fd);
	if (pid[0] == -1)
		return (ft_close_fd(vars->fd), ft_free_vars(vars), errno);
	pid[1] = ft_exec_last(vars, vars->cmds[1], vars->fd, vars->file_out);
	if (pid[1] == -1)
		return (ft_close_fd(vars->fd), ft_free_vars(vars), errno);
	// i = 0;
	// while (i < 2)
	// {
	// 	waitpid(pid[i], NULL, 0);
	// 	i++;
	// }
	ft_close_fd(vars->fd);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}
