/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:24:45 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/05/30 01:31:10 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "libft.h"
# include "ft_printf.h"

/* Our structure */
typedef struct s_pipe {
	char	*cmd1;
	char	*cmd2;
	int		cmd1_found;
	int		cmd2_found;
	char	**args1;
	char	**args2;
	char	*file1;
	char	*file2;
	int		fd1;
	int		fd2;
	int		pid1;
	int		pid2;
}	t_pipe;

/* pipex.c */
int		return_errno(int err);
void	error_exit(t_pipe pipe);
void	run_cmd2_child(int fd[2], t_pipe pipe, char *const *envp);
void	run_cmd1_child(int fd[2], t_pipe pipe, char *const *envp);

/* args.c */
int		init_pipe(t_pipe *pipe, char **argv);
int		free_split(char **arr);

/* path.c */
int		make_exe_fullpath(t_pipe *pipe, char *path);

/* utils.c */
void	register_pipe(t_pipe *pipe);
void	init_pipex(t_pipe *pipe, char **argv, char **envp);
void	create_forks(t_pipe *pipex, int *fd, char **envp);

#endif