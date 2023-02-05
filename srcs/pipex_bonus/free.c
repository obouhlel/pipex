/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:19:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 14:27:39 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
			free(strs[i++]);
		free(strs);
	}
}

void	ft_free_vars(t_vars *vars)
{
	if (vars->limiter)
		free(vars->limiter);
	if (vars->path)
		ft_free_strs(vars->path);
	if (vars->cmds)
		free(vars->cmds);
	if (vars)
		free(vars);
}
