/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:30:06 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/05/31 00:44:43 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* A simple function to return the errno if there is one or create a new one
@param int err -> 0 for using errno, 1 for using custom error
*/
int	return_errno(int err)
{
	if (err < 1)
		errno = EAGAIN;
	else
		errno = err;
	return (-1);
}

/* Exit the program with an error message and free everything
@param t_pipe pipe -> struct that contains all the information needed
*/
void	error_exit(t_pipe pipe)
{
	free_split(pipe.args1);
	free_split(pipe.args2);
	if (pipe.cmd1_found)
		free(pipe.cmd1);
	if (pipe.cmd2_found)
		free(pipe.cmd2);
	ft_printf("Error: %s\n", strerror(errno));
	exit(errno);
}

/* The function that will be runned by the child process of cmd1
@param int fd[2] -> pipe file descriptors that will be used for the pipe
@param t_pipe pipe -> struct that contains all the information needed
@param char *const *envp -> the environment variables
*/
void	run_cmd1_child(int fd[2], t_pipe pipe, char *const *envp)
{
	if (dup2(pipe.fd1, STDIN_FILENO) == -1)
		error_exit(pipe);
	close(pipe.fd1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit(pipe);
	close(fd[0]);
	close(fd[1]);
	execve(pipe.cmd1, pipe.args1, envp);
}

/* The function that will be runned by the child process of cmd2
@param int fd[2] -> pipe file descriptors that will be used for the pipe
@param t_pipe pipe -> struct that contains all the information needed
@param char *const *envp -> the environment variables
*/
void	run_cmd2_child(int fd[2], t_pipe pipe, char *const *envp)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_exit(pipe);
	close(fd[0]);
	close(fd[1]);
	if (dup2(pipe.fd2, STDOUT_FILENO) == -1)
		error_exit(pipe);
	close(pipe.fd2);
	execve(pipe.cmd2, pipe.args2, envp);
}

/* Main function used to parse arguments
@param int argc -> Amount of input arguments (including the program name)
@param char *argv[] -> Array of arguments formatted as strings
@return int -> The program return value
*/
int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	t_pipe	pipex;

	if (argc != 5)
		return (0);
	init_pipex(&pipex, argv, envp);
	create_forks(&pipex, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.fd1, NULL, 0);
	free_split(pipex.args1);
	free_split(pipex.args2);
	if (pipex.cmd1_found)
		free(pipex.cmd1);
	if (pipex.cmd2_found)
		free(pipex.cmd2);
	return (0);
}
