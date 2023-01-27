/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/27 15:43:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	**main_pipe(const int n);
static int	main_exec(int **fd, int file[2], const int n, char **av);
static void	ft_main_close(int file[2], int **fd, const int n);

int	main(int ac, char **av)
{
	const int	n = ac - 4;
	int			**fd;
	int			file[2];

	if (ac < 5)
		return (ft_putendl_fd(ERROR_AC, STDERR_FILENO), EXIT_FAILURE);
	file[0] = open(av[1], O_RDWR);
	if (file[0] == -1)
		return (ft_error_msg());
	file[1] = ft_check_file(av, ac);
	if (file[1] == -1)
		return (errno);
	fd = main_pipe(n);
	if (!fd)
		return (EXIT_FAILURE);
	if (main_exec(fd, file, n, av) != 0)
		return (errno);
	return (EXIT_SUCCESS);
}

static int	**main_pipe(const int n)
{
	int	**fd;
	int	i;

	fd = (int **)malloc(sizeof(int *) * n);
	if (!fd)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			return (ft_free_close_all_fd(fd, n), NULL);
		if (pipe(fd[i]) == -1)
			return (ft_free_close_all_fd(fd, n), ft_error_msg(), NULL);
	}
	return (fd);
}

static int	main_exec(int **fd, int file[2], const int n, char **av)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		if (i == 0)
		{
			if (ft_exec_first(av[i + 2], file[0], fd[i]) != 0)
				return (ft_free_close_all_fd(fd, n), errno);
		}
		else if (i == n)
		{
			if (ft_exec_last(av[i + 2], fd[i - 1], file[1]) != 0)
				return (ft_free_close_all_fd(fd, n), errno);
		}
		else
		{
			if (ft_exec(av[i + 2], fd[i - 1], fd[i]) != 0)
				return (ft_free_close_all_fd(fd, n), errno);
		}
		i++;
	}
	ft_main_close(file, fd, n);
	return (EXIT_SUCCESS);
}

static void	ft_main_close(int file[2], int **fd, const int n)
{
	close(file[0]);
	close(file[1]);
	ft_free_close_all_fd(fd, n);
}
