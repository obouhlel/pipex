/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:19:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/04 17:51:09 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

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

void	ft_free_exec(char **args, char *cmd)
{
	if (args)
		ft_free_strs(args);
	if (cmd)
		free(cmd);
}

void	ft_free_vars(t_vars *vars)
{
	if (vars->path)
		ft_free_strs(vars->path);
	if (vars->cmds)
		free(vars->cmds);
	if (vars)
		free(vars);
}