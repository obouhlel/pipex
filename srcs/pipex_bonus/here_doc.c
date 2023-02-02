/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:23:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 17:11:55 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static int	main_exec_here_doc_bis(t_vars *vars);

int	main_exec_here_doc(t_vars *vars)
{
	static char	*str = "Bonjour";

	while (1)
	{
		if (str)
			ft_putstr_fd("pipe heredoc> ", STDERR_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (str && ft_strcmp(str, vars->limiter) == 0)
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
	while (i < vars->n)
	{
		if (i == 0)
		{
			if (ft_exec_first(vars, vars->cmds[i], \
				vars->fd[0][0], vars->fd[i + 1]))
				return (ft_free_vars(vars), errno);
		}
		else
		{
			if (ft_exec(vars, vars->cmds[i], vars->fd[i], vars->fd[i + 1]))
				return (ft_free_vars(vars), errno);
		}
		i++;
	}
	if (ft_exec_last(vars, vars->cmds[i], vars->fd[i], vars->file_out))
		return (ft_free_vars(vars), errno);
	i = -1;
	while (++i <= vars->n)
		wait(NULL);
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}
