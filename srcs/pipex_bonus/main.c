/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 14:28:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	vars = NULL;
	if (ac != 5)
		return (ft_error(NULL, ERROR_AC, NULL), EXIT_FAILURE);
	vars = ft_init_vars(ac, av, env);
	if (!vars)
		return (EXIT_FAILURE);
	if (main_exec(vars))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
