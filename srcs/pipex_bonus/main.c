/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 17:11:25 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static int	main_exec(t_vars *vars);

int	main(int ac, char **av)
{
	t_vars	*vars;

	vars = NULL;
	if (ac < 5)
		return (ft_putendl_fd(ERROR_AC, STDERR_FILENO), EXIT_FAILURE);
	vars = ft_init_vars(ac, av);
	if (!vars)
		return (EXIT_FAILURE);
	if (vars->here_doc && ac < 6)
		return (ft_free_vars(vars), ft_putendl_fd(ERROR_ACHD, 2), EXIT_FAILURE);
	if (vars->here_doc == 0)
	{
		if (main_exec(vars))
			return (errno);
	}
	else
	{
		if (main_exec_here_doc(vars))
			return (ft_free_vars(vars), errno);
	}
	return (EXIT_SUCCESS);
}

static int	main_exec(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->n)
	{
		if (i == 0)
		{
			if (ft_exec_first(vars, vars->cmds[i], vars->file_in, vars->fd[i]))
				return (ft_free_vars(vars), errno);
		}
		else
		{
			if (ft_exec(vars, vars->cmds[i], vars->fd[i - 1], vars->fd[i]))
				return (ft_free_vars(vars), errno);
		}
		i++;
	}
	if (ft_exec_last(vars, vars->cmds[i], vars->fd[i - 1], vars->file_out))
		return (ft_free_vars(vars), errno);
	wait(NULL);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}
