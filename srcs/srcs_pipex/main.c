/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 21:02:26 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int		**fd;
	int		n;
	int		file_out;
	int		i;

	//Check Args
	if (ac < 5)
		return (ft_putendl_fd(ERROR_AC, STDERR_FILENO), EXIT_FAILURE);
	//Check infile, and outfile
	file_out = ft_check_file(av, ac);
	if (file_out == -1)
		return (errno);
	//Create and open all fd (0 for read, 1 for write)
	n = ac - 4;
	fd = (int **)malloc(sizeof(int *) * n);
	if (!fd)
		return (EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			return (ft_free_close_all_fd(fd, n), EXIT_FAILURE);
		if (pipe(fd[i]) == -1)
			return (ft_free_close_all_fd(fd, n), ft_error_msg());
		i++;
	}
	//Exec cmds
	i = 0;
	while (i <= n)
	{
		if (i == 0)
		{
			if (ft_exec_first(av[i + 2], fd[i][WRITE]) != 0)
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
	return (EXIT_SUCCESS);
}
