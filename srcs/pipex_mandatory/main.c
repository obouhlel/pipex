/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 18:59:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	vars = NULL;
	if (ac != 5)
		return (ft_error(NULL, ERROR_AC, NULL), EXIT_FAILURE);
	if (ft_check_file(av[1], av[ac - 1]) == FAIL)
		return (EXIT_FAILURE);
	vars = ft_init_vars(ac, av, env);
	if (!vars)
		return (EXIT_FAILURE);
	if (vars && ft_check_cmds(vars->cmds))
		return (ft_error(vars, ERROR_CMD, &ft_close_fd), EXIT_FAILURE);
	if (vars && main_exec(vars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
