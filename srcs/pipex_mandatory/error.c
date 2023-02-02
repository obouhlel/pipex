/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 17:22:05 by obouhlel         ###   ########.fr       */
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
