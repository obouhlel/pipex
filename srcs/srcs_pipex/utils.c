/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/29 13:29:29 by obouhlel         ###   ########.fr       */
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

int	ft_check_file_out(int ac, char **av)
{
	char *const	argv[] = {"touch", av[ac - 1], NULL};
	int			file_out;
	int			id;

	file_out = open(av[ac - 1], O_RDWR);
	if (file_out == -1)
	{
		id = fork();
		if (id == -1)
			return (ft_putendl_fd(strerror(errno), 2), file_out);
		if (id == 0)
		{
			execve("/usr/bin/touch", argv, NULL);
			ft_putendl_fd(strerror(errno), 2);
			exit(errno);
		}
		else
			wait(NULL);
	}
	if (errno)
		return (-1);
	file_out = open(av[ac - 1], O_RDWR);
	return (file_out);
}
