/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/24 15:18:23 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	main(int ac, char **av)
{
	int		id[2];
	int		fd[2];
	int		file_out;

	if (ac != 5)
		return (EXIT_FAILURE);
	file_out = ft_check_file(av);
	if (file_out == -1)
		return (errno);
	if (pipe(fd) == -1)
		return (errno);
	id[0] = fork();
	if (id[0] == -1)
		return (errno);
	if (id[0] == 0)
		ft_exec_cmd1(file_out, fd, av);
	else
		wait(NULL);
	id[1] = fork();
	if (id[1] == -1)
		return (errno);
	if (id[1] == 0)
		ft_exec_cmd2(file_out, fd, av);
	return (EXIT_SUCCESS);
}
