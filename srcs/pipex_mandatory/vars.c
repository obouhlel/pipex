/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:07:10 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 18:41:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	*ft_init_vars_cmds(t_vars *vars, char **av);
static void	*ft_init_vars_file(int ac, char **av, t_vars *vars);

t_vars	*ft_init_vars(int ac, char **av)
{
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(sizeof(t_vars), 1);
	if (!vars)
		return (NULL);
	vars->n = ac - 4;
	if (!ft_init_vars_cmds(vars, av))
		return (ft_free_vars(vars), NULL);
	if (!ft_init_vars_file(ac, av, vars))
		return (ft_free_vars(vars), NULL);
	if (pipe(vars->fd) == -1)
		return (ft_putendl_fd(strerror(errno), 2), ft_free_vars(vars), NULL);
	return (vars);
}

static void	*ft_init_vars_cmds(t_vars *vars, char **av)
{
	int	i;

	vars->cmds = (char **)malloc(sizeof(char *) * (vars->n + 2));
	if (!vars->cmds)
		return (ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), NULL);
	i = 0;
	while (i <= vars->n)
	{
		vars->cmds[i] = av[2 + i];
		i++;
	}
	vars->cmds[i] = NULL;
	return (SUCCESS);
}

static void	*ft_init_vars_file(int ac, char **av, t_vars *vars)
{
	vars->file_in = open(av[1], O_RDONLY);
	if (vars->file_in == -1)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	vars->file_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->file_out == -1)
		return (ft_putendl_fd(strerror(errno), STDERR_FILENO), NULL);
	return (SUCCESS);
}

void	ft_free_vars(t_vars *vars)
{
	if (vars->cmds)
		free(vars->cmds);
	if (vars)
		free(vars);
}
