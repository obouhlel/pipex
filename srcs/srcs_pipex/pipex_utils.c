/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:18:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/01/26 10:12:58 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_error_msg(void)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(errno);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	ft_exec_cmd1(int file_out, int fd[2], char **av)
{
	char	**argv;
	char	*cmd;

	close(file_out);
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_error_msg());
	close(fd[1]);
	argv = ft_split(av[2], ' ');
	if (!argv)
		return (ft_error_msg());
	cmd = ft_strjoin("/usr/bin/", argv[0]);
	if (!cmd)
		return (ft_free_strs(argv));
	if (access(cmd, R_OK) == -1)
		return (ft_free_strs(argv), free(cmd), ft_error_msg());
	execve(cmd, argv, NULL);
	ft_error_msg();
}

void	ft_exec_cmd2(int file_out, int fd[2], char **av)
{
	char	**argv;
	char	*cmd;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (ft_error_msg());
	if (dup2(file_out, STDOUT_FILENO) == -1)
		return (ft_error_msg());
	close(fd[0]);
	close(file_out);
	argv = ft_split(av[3], ' ');
	if (!argv)
		return (ft_error_msg());
	cmd = ft_strjoin("/usr/bin/", argv[0]);
	if (!cmd)
		return (ft_free_strs(argv));
	if (access(cmd, R_OK) == -1)
		return (ft_free_strs(argv), free(cmd), ft_error_msg());
	execve(cmd, argv, NULL);
	ft_error_msg();
}

int	ft_check_file(char **av, int ac)
{
	char *const	argv[] = {"touch", av[4], NULL};
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
