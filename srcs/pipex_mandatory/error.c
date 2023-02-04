/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/04 18:34:50 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_error(t_vars *vars, char *msg, void (*f)(int *))
{
	ft_putendl_fd(msg, STDERR);
	if (f)
		f(vars->fd);
	if (vars)
		ft_free_vars(vars);
}

void	ft_error_exit(t_vars *vars, char *msg, int exit_code, void (*f)(int *))
{
	ft_putendl_fd(msg, STDERR);
	if (f)
		f(vars->fd);
	if (vars)
		ft_free_vars(vars);
	exit(exit_code);
}
