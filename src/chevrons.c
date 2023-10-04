/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:17:38 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/04 20:00:26 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

/*cmd->fd_pipe MUST BE INITIALIZED BEFORE ENTERING ANY OF THESE FUNCTIONS*/

/*This function saves the input in a new fd. It should be called right
  before the execution function*/
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
		write(cmd->fd_pipe[1], line, ft_strlen(line));
		free(line);
		write(cmd->fd_pipe[1], "\n", 1);
		line = readline("> ");
	}
	free(line);
	close(cmd->fd_pipe[1]);
	return (0);
}

/*This function redirects the reading fd to the one specified*/
int	open_chev(t_cmd *cmd)
{
	cmd->fd_pipe[0] = open(cmd->arg, O_RDONLY);
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

/*This function redirects the writing fd to the one specified and, depending
  on the append value, it will delete the previous content of the file or append
  the new text to it*/
int	close_chev(t_cmd *cmd, int append)
{
	if (!append)
		cmd->fd_pipe[1] = open(cmd->arg, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->fd_pipe[1] = open(cmd->arg, O_WRONLY | O_CREAT | O_APPEND, 0666);
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

int	executor(t_parsing *parsing, t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (parsing->heredoc)
		{
			if (here_doc(cmd, "eof") == -1)
			{
				perror("heredoc");
				exit(EXIT_FAILURE);
			}
			if (dup2(cmd->fd_pipe[0], 0) == -1)
				return (-1);
			close(cmd->fd_pipe[1]);
		}
		if (parsing->re_output)
		{
			if (close_chev(cmd, 0) == -1)
			{
				perror("close chev");
				exit(EXIT_FAILURE);
			}
		}
		execve(cmd->cmd[0], cmd->cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{    
		pid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
		if (pid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			printf("exited, status=%d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("killed by signal %d\n", WTERMSIG(status));
		}
		else if (WIFSTOPPED(status))
		{
			printf("stopped by signal %d\n", WSTOPSIG(status));
		}
		else if (WIFCONTINUED(status))
		{
			printf("continued\n");
		}
        exit(EXIT_SUCCESS);
	}
	return (0);
}
/*
int	main()
{
	t_parsing	parsing;
	t_cmd		cmd;

	parsing.heredoc = 1;
	parsing.eof = ft_strdup("eof");
	parsing.re_input = 0;
	parsing.re_output = 0;

	cmd.cmd = malloc(sizeof(char **));
	cmd.cmd[0] = ft_strdup("/bin/cat");
	cmd.cmd[1] = NULL;
	cmd.arg = ft_strdup("file2");
	cmd.fd_pipe[0] = 0;
	cmd.fd_pipe[1] = 1;
	cmd.std[0] = dup(0);
	cmd.std[1] = dup(1);

	executor(&parsing, &cmd);
}*/
