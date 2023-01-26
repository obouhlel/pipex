/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 11:51:30 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	main(int ac, char **av)
{
	t_list	*list;
	int		*id;
	int		**fd;
	int		file_out;
	int		i;

	if (ac < 5)
		return (ft_putendl_fd(ERROR_AC, STDERR_FILENO), EXIT_FAILURE);
	list = malloc(sizeof(t_list));
	if (!list)
		return (ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), EXIT_FAILURE);
	list->n = ac;
	file_out = ft_check_file(av, ac);
	if (file_out == -1)
		return (errno);
	id = ft_calloc(ac, sizeof(int));
	if (!id)
		return (ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), EXIT_FAILURE);
	list->id = id;
	i = 0;
	fd = malloc(2 * sizeof(int));
	if (!fd)
		return (ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), EXIT_FAILURE);
	while (i < 2)
	{
		fd[i] = ft_calloc((ac - 1), sizeof(int));
		if (!fd[i])
			return (ft_free_id_fd(id, fd, ac), \
			ft_putendl_fd(ERROR_MALLOC, STDERR_FILENO), EXIT_FAILURE);
		i++;
	}
	list->fd = fd;
	i = 0;
	while (i < ac)
	{
		if (pipe(fd[i]) == -1)
			return (ft_free_id_fd(id, fd, ac), ft_error_msg(), errno);
		i++;
	}
	i = 0;
	while (i < ac)
	{
		list->cmd = av[i + 1];
		if (i == 0)
			ft_exec_first(list, id[i], fd[i][WRITE]);
		else if (i == ac - 1)
			ft_exec_last(list, id[i], fd[i - 1][READ], file_out);
		else
			ft_exec(list, id[i], fd[i - 1][READ], fd[i][WRITE]);
		i++;
	}
	return (EXIT_SUCCESS);
}
