/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 11:52:27 by obouhlel         ###   ########.fr       */
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

void	ft_free_id_fd(int *id, int **fd, int n)
{
	if (id)
		free(id);
	ft_close_all(fd, n);
	if (fd[0])
		free(fd[0]);
	if (fd[1])
		free(fd[1]);
}

void	ft_free_all(t_list *list)
{
	int	i;

	ft_free_id_fd(list->id, list->fd, list->n);
	i = 0;
	if (list->strs)
	{
		while (list->strs[i])
			free(list->strs[i++]);
		free(list->strs);
	}
}

void	ft_close_all(int **fd, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		if (fd[i])
		{
			j = 0;
			while (j < 2)
				close(fd[i][j++]);
		}
		i++;
	}
}

int	ft_check_file(char **av, int ac)
{
	char *const	argv[] = {"touch", av[ac - 1], NULL};
	int			file_out;
	int			id;

	file_out = -1;
	if (open(av[1], O_RDONLY) == -1)
		return (ft_putendl_fd(strerror(errno), 2), file_out);
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
	file_out = open(av[ac - 1], O_RDWR);
	return (file_out);
}
