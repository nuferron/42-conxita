#include "../../conxita.h"

/*Redirects the file desccriptors according with the input*/
int	redirections(t_cmd *cmd, t_redir *redir)
{
	int	err;
	
	dprintf(2, "\033[1;36mredirections: input %d\toutput %d\033[m\n", cmd->input, cmd->output);
	err = 0;
	if (cmd->input == infile)
		err = dup2(cmd->infd, 0);
	else if (cmd->input == ipipe)
		err = dup2(redir->fdr_aux, 0);
	else if (cmd->input == stdi)
		err = dup2(redir->saved_std[0], 0);
	if (err == -1)
		return (-1);
	if (cmd->output == opipe)
		err = dup2(redir->fd_pipe[1], 1);
	else if (cmd->output == stdo)
		err = dup2(redir->saved_std[1], 1);
	else if (cmd->output == f_trunc || cmd->output == f_append)
		err = dup2(cmd->outfd, 1);
	if (err == -1)
		return (-1);
	if (close(redir->saved_std[0]) == -1 || close(redir->saved_std[1]) == -1
		|| close(redir->fd_pipe[0]) == -1 || close(redir->fd_pipe[1]) == -1)
		return (-1);
	return (0);
}

/*Well, it executes the command... it also returns de pid of the child*/
pid_t	exec_cmd(t_cmd *cmd, t_redir *redir)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		dprintf(2, "exec_cmd says hi\n");
		redirections(cmd, redir);
		if (execve(cmd->cmd[0], cmd->cmd, NULL) == -1)
		{
			if (access(cmd->cmd[0], X_OK) == -1)
				printf("conxita: %s: command not found\n", cmd->cmd[0]);
			else
				print_errors(NULL);
			exit(1);
		}
	}
	return (pid);
}

/*Opens and returns the output's fd. It can be truncated (>) or appended (>>)*/
int	get_out_fd(t_cmd *cmd)
{
	int	fd;

	if (cmd->output == f_trunc)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (cmd->output == f_append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if ((cmd->output == f_trunc || cmd->output == f_append) && fd == -1)
	{
		printf("Bad file descriptor\n");
		exit(127);
	}
	return (fd);
}

/*It basically calls the redirection and the execution functions*/
int	lets_execute(t_cmd *cmd, t_redir *redir, int len)
{
	int		i;
	pid_t	pid;

	i = -1;
	if (!cmd || !redir)
		return (print_errors(NULL));
	while (++i < len)
	{
		dprintf(2, "lets exec %s in %d out %d\n", cmd[i].cmd[0], cmd[i].input, cmd[i].output);
	}
	i = -1;
	while (++i < len)
	{
		dprintf(2, "lets execute says hi\n");
		if (pipe(redir->fd_pipe) == -1)
			return (-1);
		cmd[i].outfd = get_out_fd(&cmd[i]);
		pid = exec_cmd(&cmd[i], redir);
		if ((cmd[i].outfile && close(cmd[i].outfd) == -1)
			|| close(redir->fd_pipe[1]) == -1
			|| (redir->fdr_aux > 0 && close(redir->fdr_aux) == -1))
			return (print_errors(NULL));
		redir->fdr_aux = redir->fd_pipe[0];
	}
	if (close(redir->saved_std[0]) == -1 || close(redir->saved_std[1]) == -1
		|| close(redir->fd_pipe[0]) == -1)
		return (-1);
	return (pid);
}
