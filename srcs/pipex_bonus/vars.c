/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:07:10 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 21:28:32 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

t_vars	*ft_init_vars(int ac, char **av, char **env)
{
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(sizeof(t_vars), 1);
	if (!vars)
		return (NULL);
	ft_init_vars_bis(vars, ac, av);
	if (vars->here_doc && !vars->limiter)
		return (ft_error(vars, ERROR_MALLOC, NULL), NULL);
	vars->path = ft_get_path(env);
	if (!vars->path)
		return (ft_error(vars, ERROR_PATH, NULL), NULL);
	vars->cmds = ft_init_vars_cmds(av, (vars->nb_pipes + 1));
	if (!vars->cmds)
		return (ft_error(vars, ERROR_MALLOC, NULL), NULL);
	vars->pipes = ft_init_vars_pipes(vars);
	if (!vars->pipes)
		return (ft_error(vars, ERROR_MALLOC, NULL), NULL);
	else if (vars->pipes == PIPE_FAIL)
		return (ft_error(vars, strerror(errno), NULL), NULL);
	return (vars);
}

void	ft_init_vars_bis(t_vars *vars, int ac, char **av)
{
	vars->nb_pipes = ac - 4;
	vars->here_doc = NORMAL;
	if (ft_strcmp("here_doc", av[1]) == 0)
		vars->here_doc = HERE_DOC;
	if (vars->here_doc == HERE_DOC)
	{
		vars->limiter = ft_strjoin(av[1], "\n");
		vars->infile = NULL;
	}
	else
	{
		vars->limiter = NULL;
		vars->infile = av[1];
	}
	vars->outfile = av[ac - 1];
}

char	**ft_init_vars_cmds(char **av, int nb_cmds)
{
	char	**cmds;
	int		i;

	cmds = NULL;
	cmds = (char **)malloc(sizeof(char *) * (nb_cmds + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < nb_cmds)
	{
		cmds[i] = av[2 + i];
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

int	**ft_init_vars_pipes(t_vars *vars)
{
	int	**pipes;
	int	i;

	pipes = (int **)ft_calloc(sizeof(int **), \
			(vars->nb_pipes + vars->here_doc));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < (vars->nb_pipes + vars->here_doc))
	{
		pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (pipes[i])
			return (ft_free_pipes(pipes, (vars->nb_pipes + \
										vars->here_doc)), NULL);
		i++;
	}
	i = 0;
	while (i < (vars->nb_pipes + vars->here_doc))
	{
		if (pipe(pipes[i]) == FAIL)
			return (ft_close_pipes(vars), PIPE_FAIL);
		i++;
	}
	return (pipes);
}
