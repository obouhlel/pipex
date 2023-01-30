/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:07:10 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/30 08:50:10 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	*ft_init_vars_file(int ac, char **av, t_vars *vars);
static void	*ft_init_vars_pipe(t_vars *vars);

t_vars	*ft_init_vars(int ac, char **av)
{
	t_vars	*vars;
	int		i;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->n = ac - 4;
	vars->here_doc = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		vars->here_doc = 1;
	vars->cmds = (char **)malloc(sizeof(char *) * (vars->n + 2));
	if (!vars->cmds)
		return (free(vars), NULL);
	i = 0;
	while (i <= vars->n)
	{
		vars->cmds[i] = av[2 + i];
		i++;
	}
	vars->cmds[i] = NULL;
	if (!ft_init_vars_file(ac, av, vars))
		return (free(vars->cmds), free(vars), NULL);
	if (!ft_init_vars_pipe(vars))
		return (free(vars->cmds), free(vars), NULL);
	return (vars);
}

static void	*ft_init_vars_file(int ac, char **av, t_vars *vars)
{
	vars->file_in = open(av[1], O_RDONLY);
	if (vars->file_in == -1)
		return (ft_putendl_fd(strerror(errno), STDERR_FILENO), NULL);
	vars->file_out = ft_check_file_out(ac, av);
	if (vars->file_out == -1)
		return (ft_putendl_fd(strerror(errno), STDERR_FILENO), NULL);
	return (SUCCESS);
}

static void	*ft_init_vars_pipe(t_vars *vars)
{
	int	**fd;
	int	i;

	fd = (int **)malloc(sizeof(int *) * vars->n);
	if (!fd)
		return (NULL);
	i = 0;
	while (i < vars->n)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			return (ft_free_close_all_fd(fd, vars->n), NULL);
		if (pipe(fd[i]) == -1)
			return (ft_free_close_all_fd(fd, vars->n), \
					ft_putendl_fd(strerror(errno), STDERR_FILENO), NULL);
		i++;
	}
	vars->fd = fd;
	return (SUCCESS);
}

void	ft_free_vars(t_vars *vars)
{
	close(vars->file_in);
	close(vars->file_out);
	if (vars->cmds)
		free(vars->cmds);
	if (vars->fd)
		ft_free_close_all_fd(vars->fd, vars->n);
	if (vars)
		free(vars);
}
