/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:23:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 21:07:25 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main_exec_here_doc(t_vars *vars)
{
	static char	*str = "Bonjour";

	while (str)
	{
		ft_putstr_fd("pipe heredoc> ", STDERR);
		str = get_next_line(STDIN);
		if (!str)
			break ;
		if (str && ft_strcmp(str, vars->limiter) == 0)
		{
			free(str);
			close(vars->pipes[0][W]);
			break ;
		}
		ft_putstr_fd(str, vars->pipes[0][W]);
		free(str);
	}
	return (EXIT_SUCCESS);
}
