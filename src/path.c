/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:32:23 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/05/31 00:36:41 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* A simple function to bypass the norminette concatenating the path and the cmd
@param char *new -> the string pointer we will copy to
@param size_t idx -> index used to know from where to start copying
@param char **path -> the path we found and that we will concatenate
@param char **cmd -> the command that will concatenate to the path
*/
void	link_filepath(char *new, size_t idx, char **path, char **cmd)
{
	ft_strlcpy(new, path[idx], -1);
	ft_strlcat(new, "/", -1);
	ft_strlcat(new, *cmd, -1);
}

/* Find the correct env path for a command
@param char **path -> the path we found and that we will concatenate
@param char **cmd -> the command that will concatenate to the path
@return int -> Success (0) or Failure (-1)
*/
int	find_path_for_cmd(char **path, char **cmd)
{
	size_t	idx;
	char	*new;

	idx = 0;
	while (path[idx])
	{
		new = malloc(ft_strlen(path[idx]) + ft_strlen(*cmd) + 2);
		if (!new)
			return (return_errno(ENOMEM));
		link_filepath(new, idx, path, cmd);
		if (access(new, X_OK | F_OK) == -1)
		{
			free(new);
			new = NULL;
		}
		else
		{
			*cmd = new;
			break ;
		}
		idx++;
	}
	if (!new)
		return (return_errno(ESRCH));
	return (0);
}

/* Transform the command into the parent env path + / + the command
@param t_pipe *pipe -> the struct that contains all the information needed
@param char **cmd -> the command that will concatenate to the path
@return int -> Success (0) or Failure (-1)
*/
int	make_exe_fullpath(t_pipe *pipe, char *path)
{
	char	**arr;

	if (!pipe->cmd1)
		return (return_errno(EINVAL));
	if (!pipe->cmd2)
		return (return_errno(EINVAL));
	arr = ft_split(path + 5, ':');
	if (!arr)
		return (return_errno(ENOMEM));
	if (find_path_for_cmd(arr, &(pipe->cmd1)) == -1)
		return (return_errno(ENOMEM));
	pipe->cmd1_found = 1;
	if (find_path_for_cmd(arr, &(pipe->cmd2)) == -1)
		return (return_errno(ENOMEM));
	pipe->cmd2_found = 1;
	free_split(arr);
	return (0);
}
