/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:19:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 19:02:55 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_vars_and_tmp(t_vars *vars, char *tmp)
{
	if (vars)
		ft_free_vars(vars);
	if (tmp)
		ft_free((void **)tmp);
}

void	ft_free_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipes[i])
			ft_free((void **)&pipes[i]);
		i++;
	}
	if (pipes)
		free(pipes);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
			ft_free((void **)&strs[i++]);
		free(strs);
	}
}

void	ft_free_vars(t_vars *vars)
{
	ft_close_pipes(vars);
	if (vars->limiter)
		ft_free((void **)&vars->limiter);
	if (vars->path)
		ft_free_strs(vars->path);
	if (vars->cmds)
		ft_free((void **)&vars->cmds);
	if (vars->pipes)
	{
		ft_free_pipes(vars->pipes, (vars->nb_pipes + vars->here_doc));
		vars->pipes = NULL;
	}
	if (vars->pid)
		ft_free((void **)&vars->pid);
	if (vars)
		ft_free((void **)&vars);
}
