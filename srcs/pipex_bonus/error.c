/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 21:14:43 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_error_exec(t_vars *vars, char **args, char *tmp, char *msg)
{
	if (vars)
		ft_free_vars(vars);
	if (args)
		ft_free_strs(args);
	if (tmp)
		free(tmp);
	if (msg)
		ft_putendl_fd(msg, STDERR);
	exit(EXIT_FAILURE);
}

void	ft_error(t_vars *vars, char *msg, void (*ft_close)(t_vars *))
{
	if (msg)
		ft_putendl_fd(msg, STDERR);
	if (ft_close)
		ft_close(vars);
	if (vars)
		ft_free_vars(vars);
}

void	ft_error_exit(t_vars *vars, char *msg, void (*ft_close)(t_vars *))
{
	ft_putendl_fd(msg, STDERR);
	if (ft_close)
		ft_close(vars);
	if (vars)
		ft_free_vars(vars);
	exit(errno);
}
