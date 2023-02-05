/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:19:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/05 14:32:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

char	*ft_access(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!tmp)
			return (ft_error(NULL, ERROR_MALLOC, NULL), free(cmd), NULL);
		if (access(tmp, X_OK) != FAIL)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	**ft_get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	ft_close_fd(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->fd)
	{
		while (i < vars->n)
		{
			if (vars->fd[i])
			{
				if (vars->fd[i][R])
					close(vars->fd[i][R]);
				if (vars->fd[i][W])
					close(vars->fd[i][W]);
			}
			i++;
		}
	}
}
