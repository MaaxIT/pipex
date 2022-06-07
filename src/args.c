/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:32:28 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/05/31 00:41:17 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* A simple function to read files the user asked for
@param t_pipe *pipe -> the pipe structure used to run the program
*/
void	read_files(t_pipe *pipe)
{
	int	fd1;
	int	fd2;

	if (access(pipe->file1, F_OK | R_OK) == -1)
		error_exit(*pipe);
	fd1 = open(pipe->file1, O_RDONLY);
	if (fd1 == -1)
		error_exit(*pipe);
	fd2 = open(pipe->file2, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd2 == -1)
		error_exit(*pipe);
	pipe->fd1 = fd1;
	pipe->fd2 = fd2;
}

/* A simple function to free the split we made 
@param char **arr -> The array to free
@return int -> Will be -1 in any case, just used to return an error later
*/
int	free_split(char **arr)
{
	size_t	idx;

	if (!arr)
		return (-1);
	idx = 0;
	while (arr[idx])
		free(arr[idx++]);
	free(arr);
	return (-1);
}

/* Parse the arguments we enter and allocate what we need 
@param t_pipe *pipe -> the pipe structure used to run the program
@param char **argv -> the arguments the user has entered
@return int -> Success (0) or Failure (-1)
*/
int	init_pipe(t_pipe *pipe, char **argv)
{
	char	**arr1;
	char	**arr2;

	pipe->file1 = argv[1];
	pipe->file2 = argv[4];
	arr1 = ft_split(argv[2], ' ');
	if (!arr1)
		return (-1);
	arr2 = ft_split(argv[3], ' ');
	if (!arr2)
		return (-1);
	pipe->cmd1 = arr1[0];
	pipe->cmd2 = arr2[0];
	pipe->args1 = arr1;
	pipe->args2 = arr2;
	read_files(pipe);
	return (0);
}
