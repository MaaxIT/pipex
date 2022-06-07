/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:30:16 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/05/31 00:36:03 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Register pipe structure - basically set everything to NULL
@param t_pipe *pipe -> pointer to the pipe structure
*/
void	register_pipe(t_pipe *pipe)
{
	pipe->cmd1_found = 0;
	pipe->cmd2_found = 0;
	pipe->fd1 = -1;
	pipe->fd2 = -1;
	pipe->cmd1 = NULL;
	pipe->cmd2 = NULL;
	pipe->args1 = NULL;
	pipe->args2 = NULL;
}

/* Initialize pipe values and find full executable path
@param t_pipe *pipe -> pointer to the pipe structure
@param char **argv -> pointer to argv from main
@param char **envp -> pointer to envp from main
*/
void	init_pipex(t_pipe *pipe, char **argv, char **envp)
{
	int	i;

	register_pipe(pipe);
	if (init_pipe(pipe, argv) == -1)
	{
		return_errno(ENOMEM);
		error_exit(*pipe);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			if (make_exe_fullpath(pipe, envp[i]) == -1)
				error_exit(*pipe);
			break ;
		}
		i++;
	}
}

/* Create our child forks (process)
@param t_pipe *pipe -> pointer to the pipe structure
@param int *fd -> array of file descriptors used by the pipe
@param char **envp -> pointer to envp from main
*/
void	create_forks(t_pipe *pipex, int *fd, char **envp)
{
	if (pipe(fd) == -1)
	{
		ft_printf("An error has occured when creating the pipe\n");
		exit(1);
	}
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		ft_printf("An error has occured when creating the fork (pid1)\n");
		exit(2);
	}
	if (pipex->pid1 == 0)
		run_cmd1_child(fd, *pipex, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		ft_printf("An error has occured when creating the fork (pid2)\n");
		exit(3);
	}
	if (pipex->pid2 == 0)
		run_cmd2_child(fd, *pipex, envp);
}
