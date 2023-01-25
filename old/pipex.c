/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:03:34 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/25 11:48:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_error_msg(void)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (errno);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

int	ft_check_file(char **av)
{
	char *const	argv[] = {"touch", av[4], NULL};
	int			file_out;
	int			id;

	file_out = -1;
	if (open(av[1], O_RDONLY) == -1)
		return (ft_putendl_fd(strerror(errno), 2), file_out);
	file_out = open(av[4], O_RDWR);
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
	file_out = open(av[4], O_RDWR);
	return (file_out);
}

int	main(int ac, char **av)
{
	int		id[3];
	char	*cmd;
	char	**argv;
	int		fd[2];
	int		file_out;

	// Check the number of argument
	if (ac != 5)
		return (EXIT_FAILURE);
	// Check the file if it's exist or not, if not exist
	// I create the file
	file_out = ft_check_file(av);
	if (file_out == -1)
		return (ft_error_msg());
	// Create two pipe, fd[0] for read, fd[1] for write
	if (pipe(fd) == -1)
		return (ft_error_msg());
	// Create two processus
	id[0] = fork();
	if (id[0] == -1)
		return (ft_error_msg());
	// The Children do
	if (id[0] == 0)
	{
		// Duplicate the fd of file and close, to send the execution
		close(file_out);
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (ft_error_msg());
		close(fd[1]);
		// Take just the command and split the arg of cmd
		argv = ft_split(av[2], ' ');
		if (!argv)
			return (EXIT_FAILURE);
		// Add the path of the cmd
		cmd = ft_strjoin("/usr/bin/", argv[0]);
		if (!cmd)
			return (ft_free_strs(argv), EXIT_FAILURE);
		// Check the access if it's ok or not
		if (access(cmd, R_OK) == -1)
			return (ft_free_strs(argv), free(cmd), ft_error_msg());
		// Excecute the cmd
		execve(cmd, argv, NULL);
		return (ft_error_msg());
	}
	else
		wait(NULL);
	id[1] = fork();
	if (id[1] == -1)
		return (ft_error_msg());
	// The Children do
	if (id[1] == 0)
	{
		// Duplicate the fd of file and close, to send the execution
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (ft_error_msg());
		if (dup2(file_out, STDOUT_FILENO) == -1)
			return (ft_error_msg());
		close(fd[0]);
		close(file_out);
		// Take just the command and split the arg of cmd
		argv = ft_split(av[3], ' ');
		if (!argv)
			return (EXIT_FAILURE);
		// Add the path of the cmd
		cmd = ft_strjoin("/usr/bin/", argv[0]);
		if (!cmd)
			return (ft_free_strs(argv), EXIT_FAILURE);
		// Check the access if it's ok or not
		if (access(cmd, R_OK) == -1)
			return (ft_free_strs(argv), free(cmd), ft_error_msg());
		// Excecute the cmd
		execve(cmd, argv, NULL);
		return (ft_error_msg());
	}
	return (EXIT_SUCCESS);
}
