/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:19:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/07 19:14:13 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_check_file(char *infile, char *outfile)
{
	if (ft_strcmp(infile, "") == 0)
		return (ft_error(NULL, ERROR_NO_FILE, NULL), FAIL);
	if (ft_strcmp(outfile, "") == 0)
		return (ft_error(NULL, ERROR_NO_FILE, NULL), FAIL);
	return (SUCCESS);
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

void	ft_close_fd(int fd[2])
{
	if (fd)
	{
		if (fd[0])
			close(fd[0]);
		if (fd[1])
			close(fd[1]);
	}
}
