/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:07:10 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 15:06:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	*ft_init_vars_cmds(t_vars *vars, char **av);
static void	*ft_init_vars_file(int ac, char **av, t_vars *vars);
static void	*ft_init_vars_pipe(t_vars *vars);

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
	if (!ft_init_vars_pipe(vars))
		return (ft_free_vars(vars), NULL);
	return (vars);
}

static void	*ft_init_vars_cmds(t_vars *vars, char **av)
{
	int	i;

	vars->cmds = (char **)malloc(sizeof(char *) * (vars->n + 2));
	if (!vars->cmds)
		return (ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), NULL);
	i = 0;
	if (vars->here_doc == 0)
	{
		while (i <= vars->n)
		{
			vars->cmds[i] = av[2 + i];
			i++;
		}
		vars->cmds[i] = NULL;
	}
	else
	{
		while (i <= vars->n)
		{
			vars->cmds[i] = av[3 + i];
			i++;
		}
		vars->cmds[i] = NULL;
	}
	return (SUCCESS);
}

static void	*ft_init_vars_file(int ac, char **av, t_vars *vars)
{
	if (vars->here_doc == 0)
	{
		vars->limiter = NULL;
		vars->file_in = open(av[1], O_RDONLY);
		if (vars->file_in == -1)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		vars->file_out = open(av[ac - 1], O_CREAT | O_RDWR, 0666);
		if (vars->file_out == -1)
			return (ft_putendl_fd(strerror(errno), STDERR_FILENO), NULL);
	}
	else
	{
		vars->limiter = ft_strjoin(av[2], "\n");
		if (!vars->limiter)
			return (NULL);
		vars->file_in = -1;
		vars->file_out = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (vars->file_out == -1)
			return (ft_putendl_fd(strerror(errno), STDERR_FILENO), NULL);
	}
	return (SUCCESS);
}

static void	*ft_init_vars_pipe(t_vars *vars)
{
	int	**fd;
	int	i;

	fd = (int **)malloc(sizeof(int *) * (vars->n + vars->here_doc));
	if (!fd)
		return (ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), NULL);
	i = 0;
	while (i < (vars->n + vars->here_doc))
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			return (ft_free_close_all_fd(fd, vars->n), \
					ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), NULL);
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
	if (vars->file_in != -1)
		close(vars->file_in);
	if (vars->file_out != -1)
		close(vars->file_out);
	if (vars->limiter)
		free(vars->limiter);
	if (vars->cmds)
		free(vars->cmds);
	if (vars->fd)
		ft_free_close_all_fd(vars->fd, (vars->n + vars->here_doc));
	if (vars)
		free(vars);
}
