#include "../../conxita.h"

/*This function saves the input in a new fd. It should be called right
  before the execution function*/
/*must be changed so its information is saved in a special
  place (it shouldn't be overwritten)*/
int	here_doc(t_redir *redir, char *key)
{
	char	*line;
	char	*tmp;
	char	*aux;

	line = readline("> ");
	tmp = NULL;
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		aux = ft_strjoin(tmp, line);
		free(line);
		if (tmp)
			free(tmp);
		tmp = aux;
		aux = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = aux;
		line = readline("> ");
	}
	write(redir->fd_pipe[1], tmp, ft_strlen(tmp));
	write(redir->fd_pipe[1], "\n", 1);
	free(tmp);
	free(line);
	return (0);
}

/*int	open_chev(t_cmd *cmd)
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
		return (print_error());
	else if (pid == 0)
	{
		if (parsing->heredoc)
		{
			if (here_doc(cmd, "eof") == -1)
				exit(EXIT_FAILURE);
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
	}
	return (0);
}*/

int	main()
{
	//t_cmd		cmd;
	t_redir		redir;

	//cmd.cmd = malloc(sizeof(char **));
	//cmd.cmd[0] = ft_strdup("/bin/cat");
	//cmd.cmd[1] = ft_strdup("file5");
	//cmd.cmd[1] = NULL;

	redir.fd_pipe[0] = dup(0);
	redir.fd_pipe[1] = dup(1);
	//close(redir.fd_pipe[0]);
	//close(redir.fd_pipe[1]);
	//redir.saved_std[0] = dup(0);
	//redir.saved_std[1] = dup(1);

	//executor(&cmd, &redir);
	here_doc(&redir, "eof");

}
