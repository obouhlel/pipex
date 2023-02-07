/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:19:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 18:48:35 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

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

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			if (strs[i])
				ft_free((void **)&strs[i]);
			i++;
		}
		free(strs);
	}
}

void	ft_free_vars(t_vars *vars)
{
	if (vars->path)
	{
		ft_free_strs(vars->path);
		vars->path = NULL;
	}
	if (vars->cmds)
		ft_free((void **)&vars->cmds);
	if (vars)
		ft_free((void **)&vars);
}
