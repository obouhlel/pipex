/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/31 11:41:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_error_msg_exit(void)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(errno);
}

int	ft_error_msg(void)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (errno);
}

void	ft_error_exec(char **args, char *cmd)
{
	int	i;

	if (args)
	{
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
	}
	if (cmd)
		free(cmd);
}

void	ft_free_close_all_fd(int **fd, const int n)
{
	int	i;

	i = 0;
	if (fd)
	{
		while (i < n)
		{
			if (fd[i])
			{
				if (fd[i][0])
					close(fd[i][0]);
				if (fd[i][1])
					close(fd[i][1]);
				free(fd[i]);
			}
			i++;
		}
		free(fd);
	}
}
