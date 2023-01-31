/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:23:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/31 11:30:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	main_exec_here_doc_bis(t_vars *vars);

int	main_exec_here_doc(t_vars *vars)
{
	static char	*str = "Bonjour";

	while (1)
	{
		if (str)
			ft_putstr_fd("pipe heredoc> ", STDERR_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (str && strcmp(str, vars->limiter) == 0)
		{
			free(str);
			close(vars->fd[0][1]);
			break ;
		}
		ft_putstr_fd(str, vars->fd[0][1]);
		free(str);
	}
	if (main_exec_here_doc_bis(vars))
		return (errno);
	return (EXIT_SUCCESS);
}

static int	main_exec_here_doc_bis(t_vars *vars)
{
	int	i;

	i = 0;
	while (i <= vars->n)
	{
		if (i == 0)
		{
			if (ft_exec_first(vars, vars->cmds[i], \
				vars->fd[0][0], vars->fd[i + 1]))
				return (ft_free_vars(vars), errno);
		}
		else if (i == vars->n)
		{
			if (ft_exec_last(vars, vars->cmds[i], vars->fd[i], vars->file_out))
				return (ft_free_vars(vars), errno);
		}
		else
		{
			if (ft_exec(vars, vars->cmds[i], vars->fd[i], vars->fd[i + 1]))
				return (ft_free_vars(vars), errno);
		}
		i++;
	}
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}
