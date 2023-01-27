/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/27 12:44:41 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	main_bis(int **fd, int file_out, const int n, char **av);

int	main(int ac, char **av)
{
	const int	n = ac - 4;
	int			**fd;
	int			file_out;
	int			i;

	if (ac < 5)
		return (ft_putendl_fd(ERROR_AC, STDERR_FILENO), EXIT_FAILURE);
	file_out = ft_check_file(av, ac);
	if (file_out == -1)
		return (errno);
	fd = (int **)malloc(sizeof(int *) * n);
	if (!fd)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < n)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			return (ft_free_close_all_fd(fd, n), EXIT_FAILURE);
		if (pipe(fd[i]) == -1)
			return (ft_free_close_all_fd(fd, n), ft_error_msg());
	}
	if (main_bis(fd, file_out, n, av) != 0)
		return (errno);
	return (EXIT_SUCCESS);
}

static int	main_bis(int **fd, int file_out, const int n, char **av)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		if (i == 0)
		{
			if (ft_exec_first(av[i + 2], fd[i]) != 0)
				return (ft_free_close_all_fd(fd, n), errno);
		}
		else if (i == n)
		{
			if (ft_exec_last(av[i + 2], fd[i - 1], file_out) != 0)
				return (ft_free_close_all_fd(fd, n), errno);
		}
		else
		{
			if (ft_exec(av[i + 2], fd[i - 1], fd[i]) != 0)
				return (ft_free_close_all_fd(fd, n), errno);
		}
		i++;
	}
	close(file_out);
	ft_free_close_all_fd(fd, n);
	return (EXIT_SUCCESS);
}
