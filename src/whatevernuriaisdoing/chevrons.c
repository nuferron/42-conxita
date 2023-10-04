/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:17:38 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/04 16:42:16 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

/*cmd->fd_pipe MUST BE INITIALIZED BEFORE ENTERING ANY OF THESE FUNCTIONS*/

int	here_doc(t_cmd *cmd, char *key)
{
	char	*line;

	line = readline("> ");
	if (pipe(cmd->fd_pipe) == -1)
		return (-1);
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		if (write(cmd->fd_pipe[1], &line, ft_strlen(line)) == -1)
		{
			close(cmd->fd_pipe[1]);
			close(cmd->fd_pipe[0]);
			free(line);
			return (-1);
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	return (0);
}

int	open_chev(t_cmd *cmd, char *file)
{
	cmd->fd_pipe[0] = open(file, O_RDONLY);
	if (cmd->fd_pipe[0] == -1)
		return (-1);
	if (dup2(cmd->fd_pipe[0], 0) == -1)
	{
		close(cmd->fd_pipe[0]);
		return (-1);
	}
	close(cmd->fd_pipe[0]);
	return (0);
}

int	close_chev(t_cmd *cmd, char *file, int append)
{
	if (!append)
		cmd->fd_pipe[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->fd_pipe[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (cmd->fd_pipe[1] == -1)
		return (-1);
	if (dup2(cmd->fd_pipe[1], 1) == -1)
	{
		close(cmd->fd_pipe[1]);
		return (-1);
	}
	close(cmd->fd_pipe[1]);
	return (0);
}

/*int	main()
{
	t_cmd cmd;
	char	*test[] = {"/bin/cat", NULL, NULL};

	cmd.fd_pipe[0] = 0;
	cmd.fd_pipe[1] = 1;
	//open_chev(&cmd, "file1");
	close_chev(&cmd, "file2", 1);
	if (execve(test[0], test, NULL) == -1)
		printf("fuck\n");
//	here_doc(&cmd, "eof");
	int	fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("fd count: %d\n", fd);
}*/
