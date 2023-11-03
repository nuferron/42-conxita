#include "../../conxita.h"

/*This function saves the input in a new fd. It should be called right
  before the execution function*/
/*must be changed so its information is saved in a special
  place (it shouldn't be overwritten)*/

char	*ft_strjoin3_free(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	result = ft_strjoin(tmp, str3);
	//free(str3);
	free(tmp);
	return (result);
}

int	here_doc(t_redir *redir, char *key)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	tmp = NULL;
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		tmp = ft_strjoin3_free(tmp, line, "\n");
		if (!tmp)
			return (print_errors(NULL));
		line = readline("> ");
	}
	write(redir->fd_pipe[1], tmp, ft_strlen(tmp));
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
