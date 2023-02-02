/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 16:48:48 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

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
	ft_exec_first(vars, vars->cmds[0], vars->file_in, vars->fd[0]);
	ft_exec_last(vars, vars->cmds[1], vars->fd[0], vars->file_out);
	waitpid(-1, NULL, 0);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}
