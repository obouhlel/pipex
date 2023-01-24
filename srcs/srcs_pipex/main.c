/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:08:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/24 00:57:54 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_error_msg(void)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (errno);
}

int	ft_execution(t_pipex pipex)
{
	char	*path;
	char	**av;
	int		fd[2];
	int		id;

	if (pipe(fd) == -1)
		return (ft_error_msg());
	id = fork();
	if (id == -1)
		return (ft_error_msg());
	if (id == 0)
	{
		close(fd[1]);
		av = ft_split(pipex.cmd, ' ');
		if (!av)
			return (ft_error_msg());
		path = ft_strjoin("/bin/", av[0]);
		if (!path)
			return (ft_error_msg());
		if (access(path, R_OK) == -1)
			return (ft_error_msg());
		if (execve(path, &av[1], NULL) == -1)
			return (ft_error_msg());
	}
	else
	{
		close(fd[0]);
		av = ft_split(pipex.cmd, ' ');
		if (!av)
			return (ft_error_msg());
		path = ft_strjoin("/bin/", av[0]);
		if (!path)
			return (ft_error_msg());
		if (access(path, R_OK) == -1)
			return (ft_error_msg());
		if (execve(path, &av[1], NULL) == -1)
			return (ft_error_msg());
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_pipex	pipex[2];
	int		i;

	if (ac != 5)
		return (EXIT_FAILURE);
	pipex[0].cmd = av[2];
	pipex[0].name_file = av[1];
	pipex[1].cmd = av[3];
	pipex[1].name_file = av[4];
	i = 0;
	while (i < 2)
	{
		ft_execution(pipex[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
