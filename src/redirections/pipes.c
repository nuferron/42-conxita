#include "../../conxita.h"

int	test_paths(char *path, t_cmd *cmd)
{
	int		total;
	int		count;
	char	*test;
	char	*split;

	count = -1;
	total = path_count(path, ':');
	while (++count < total)
	{
		split = mini_split(path, count);
		if (!split)
			return (-2);
		test = ft_strjoin(split, cmd->cmd[0]);
		free(split);
		if (access(test, X_OK) == 0)
			break ;
		free(test);
	}
	if (count == total)
		return (-1);
	cmd->cmd[0] = ft_strdup(test);
	free(test);
	return (0);
}

int	get_path(char **env, t_cmd *cmd)
{
	char	*path;
	int		error;

	if (ft_strchr(cmd->cmd[0], '/') && access(cmd->cmd[0], X_OK) == 0)
		return (0);
	else if (ft_strchr(cmd->cmd[0], '/') && access(cmd->cmd[0], X_OK) != 0)
		return (-1);
	path = search_env(env, "PATH=");
	if (!path)
		return (-2);
	error = test_paths(path, cmd);
	return (error);
}

/* passar redir com a parametre per no tenir un punter a cada cmd */
/* At this point, all files must already exist */

/*int	redirections(t_cmd *cmd, t_redir *redir)
{
	int	fd;

	if (cmd->input == infile)
	{
		write(2, "infile\n", 7);
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			return (-1);
		dup2(fd, 0);
		close(fd);
	}
	else if (cmd->input == stdi)
	{
		write(2, "stdi\n", 5);
		dup2(redir->saved_std[0], 0);
	}
	else if (cmd->input == ipipe)
	{
		write(2, "ipipe\n", 6);
		dup2(redir->fd_pipe[0], 0);
	}
	if (cmd->output == stdo)
	{
		write(2, "stdo\n", 5);
		dup2(redir->saved_std[1], 1);
	}
	else if (cmd->output == f_trunc)
	{
		write(2, "trunc\n", 6);
		fd = open(cmd->outfile, O_WRONLY);
		if (fd < 0)
			return (-1);
		dup2(fd, 1);
	}
	else if (cmd->output == f_append)
	{
		write(2, "append\n", 7);
		fd = open(cmd->outfile, O_WRONLY | O_APPEND);
		if (fd < 0)
			return (-1);
		dup2(fd, 1);
	}
	else if (cmd->output == opipe)
	{
		write(2, "opipe\n", 6);
		dup2(redir->fd_pipe[1], 1);
	}
	close(redir->fd_pipe[0]);
	close(redir->fd_pipe[1]);
	return (0);
}*/

t_cmd	*init_cmd_test(void)
{	
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 3);
	if (!cmd)
		return (NULL);

	cmd[0].cmd = (char **)malloc(sizeof(char *) * 4);
	cmd[0].cmd[0] = ft_strdup("/bin/cat");
	cmd[0].cmd[1] = ft_strdup("-e");
	cmd[0].cmd[2] = ft_strdup("file1");
	cmd[0].cmd[2] = NULL;
	cmd[0].cmd[3] = NULL;
	cmd[0].heredoc = NULL;
	cmd[0].infile = ft_strdup("file1");
	cmd[0].infd = open(cmd[0].infile, O_RDONLY);
	if (cmd[0].infd < 0)
		exit(printf("open cmd[0] potxo\n"));
	cmd[0].outfile = NULL;
	cmd[0].outfd = -1;
	cmd[0].output = opipe;
	cmd[0].input = infile;

	cmd[1].cmd = (char **)malloc(sizeof(char *) * 3);
	cmd[1].cmd[0] = ft_strdup("/usr/bin/wc");
	cmd[1].cmd[1] = NULL;
	cmd[1].heredoc = NULL;
	cmd[1].infile = NULL;
	cmd[1].infd = -1;
	cmd[1].outfile = NULL;
	cmd[1].outfd = -1;
	cmd[1].output = opipe;
	cmd[1].input = ipipe;

	cmd[2].cmd = (char **)malloc(sizeof(char *) * 3);
	cmd[2].cmd[0] = ft_strdup("/bin/ls");
	cmd[2].cmd[1] = NULL;
	cmd[2].cmd[2] = NULL;
	cmd[2].heredoc = NULL;
	cmd[2].infile = NULL;
	cmd[2].infd = -1;
	cmd[2].outfile = ft_strdup("outfile");
	cmd[2].outfd = -1;
	cmd[2].output = f_trunc;
	cmd[2].input = ipipe;
	return (cmd);
}

int redirections(t_cmd *cmd, t_redir *redir)
{
	if (cmd->input == infile)
	{
		dup2(cmd->infd, 0);
		close(cmd->infd);
	}
	else if (cmd->input == ipipe)
		dup2(redir->fdr_aux, 0);
	else if (cmd->input == stdi)
		dup2(redir->saved_std[0], 0);
	if (cmd->output == opipe)
		dup2(redir->fd_pipe[1], 1);
	else if (cmd->output == stdo)
		dup2(redir->saved_std[1], 1);
	else if (cmd->output == f_trunc || cmd->output == f_append)
		dup2(cmd->outfd, 1);
	close(redir->saved_std[0]);
	close(redir->saved_std[1]);
	close(redir->fd_pipe[0]);
	close(redir->fd_pipe[1]);
	return (0);
}

//obrir outfile dins del child fora de redirections

int	main(void)
{
	t_cmd	*cmd;
	t_redir	redir;
	int	i = 0;
	int	total = 3;
	int	status;
	int	pid;

	cmd = init_cmd_test();
	redir.saved_std[0] = dup(0);
	redir.saved_std[1] = dup(1);

	redir.fdr_aux = -1;
	while (i < total)
	{
		if (pipe(redir.fd_pipe) == -1)
			return (-1);
		if (cmd[i].output == f_trunc)
		{
			dprintf(2, "hello f_trunc\n");
			cmd[i].outfd = open(cmd[i].outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (cmd[i].outfd == -1)
			{
				printf("Bad file descriptor\n");
				exit(127);
			}
		}
		else if (cmd[i].output == f_append)
		{
			dprintf(2, "hello f_append\n");
			cmd[i].outfd = open(cmd[i].outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
			if (cmd[i].outfd == -1)
			{
				printf("Bad file descriptor\n");
				exit(127);
			}
		}
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			redirections(&cmd[i], &redir);
			if (execve(cmd[i].cmd[0], cmd[i].cmd, NULL) == -1)
			{
				printf("wops it failed\n");
				exit(1);
			}
		}
		close(cmd[i].outfd);
		close(redir.fd_pipe[1]);
		close(redir.fdr_aux);
		redir.fdr_aux = redir.fd_pipe[0];
		//write(2, "after execution\n", 21);
		i++;
	}
	close(redir.saved_std[0]);
	close(redir.saved_std[1]);
	i = 0;
	while (i < total)
	{
		if (waitpid(-1, &status, 0) == pid)
			exit(1); //fer tot allo de WIFEXITED etc
		i++;
	}
	exit(status);
}
