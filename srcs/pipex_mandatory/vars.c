/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:07:10 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 21:15:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

t_vars	*ft_init_vars(int ac, char **av, char **env)
{
	t_vars	*vars;
	int		i;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->nb_pipes = ac - 4;
	vars->infile = av[1];
	vars->outfile = av[ac - 1];
	vars->path = ft_get_path(env);
	if (!vars->path)
		return (ft_error(vars, ERROR_PATH, NULL), NULL);
	vars->cmds = (char **)malloc(sizeof(char *) * (vars->nb_pipes + 2));
	if (!vars->cmds)
		return (ft_error(vars, ERROR_MALLOC, NULL), NULL);
	i = -1;
	while (++i <= vars->nb_pipes)
		vars->cmds[i] = av[2 + i];
	vars->cmds[i] = NULL;
	if (pipe(vars->fd) == -1)
		return (ft_error(vars, strerror(errno), &ft_close_fd), NULL);
	return (vars);
}
