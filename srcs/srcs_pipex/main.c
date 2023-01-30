/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/30 17:39:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	main_exec(t_vars *vars);
static int	main_exec_here_doc(t_vars *vars);

int	main(int ac, char **av)
{
	t_vars	*vars;

	vars = NULL;
	if (ac < 5)
		return (ft_putendl_fd(ERROR_AC, STDERR_FILENO), EXIT_FAILURE);
	vars = ft_init_vars(ac, av);
	if (!vars)
		return (EXIT_FAILURE);
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
	while (i <= vars->n)
	{
		if (i == 0)
		{
			if (ft_exec_first(vars, vars->cmds[i], vars->file_in, vars->fd[i]))
				return (ft_free_vars(vars), errno);
		}
		else if (i == vars->n)
		{
			if (ft_exec_last(vars, vars->cmds[i], \
				vars->fd[i - 1], vars->file_out))
				return (ft_free_vars(vars), errno);
		}
		else
		{
			if (ft_exec(vars, vars->cmds[i], vars->fd[i - 1], vars->fd[i]))
				return (ft_free_vars(vars), errno);
		}
		i++;
	}
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}

static int	main_exec_here_doc(t_vars *vars)
{
	static char	*str = "Bonjour";

	vars->file_in = open("here_doc", O_WRONLY);
	if (vars->file_in == -1)
		return (errno);
	while (1)
	{
		if (str)
			ft_putstr_fd("here doc > ", STDOUT_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (str && ft_strncmp(vars->limiter, str, \
			ft_strlen(vars->limiter)) == 0)
		{
			free(str);
			break ;
		}
		write(vars->file_in, str, ft_strlen(str));
		free(str);
	}
	ft_exec_first(vars, vars->cmds[0], vars->file_in, vars->fd[0]);
	ft_exec_last(vars, vars->cmds[1], vars->fd[0], vars->file_out);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}
