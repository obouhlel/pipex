/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:19:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 19:04:22 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	ft_check_file(char *infile, char *outfile)
{
	if (ft_strcmp(infile, "") == 0)
		return (ft_error(NULL, ERROR_NO_FILE, NULL), FAIL);
	if (ft_strcmp(outfile, "") == 0)
		return (ft_error(NULL, ERROR_NO_FILE, NULL), FAIL);
	return (SUCCESS);
}

int	ft_check_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], "") == 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

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

void	ft_close_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->pipes)
	{
		while (i < (vars->nb_pipes + vars->here_doc))
		{
			if (vars->pipes[i])
			{
				if (vars->pipes[i][R])
					close(vars->pipes[i][R]);
				if (vars->pipes[i][W])
					close(vars->pipes[i][W]);
			}
			i++;
		}
	}
}
