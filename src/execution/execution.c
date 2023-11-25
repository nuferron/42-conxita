#include "../../conxita.h"

int	reset_std(t_redir *redir, int which)
{
	if (which == 0 || which == 2)
	{
		if (dup2(redir->saved_std[0], 0) == -1)
			return (print_errors(NULL));
	}
	if (which == 1 || which == 2)
	{
		if (dup2(redir->saved_std[1], 1) == -1)
			return (print_errors(NULL));
	}
	return (0);
}

/*Redirects the file desccriptors according with the input*/
int	redirections(t_cmd *cmd, t_redir *redir)
{
	int	err;

	err = 0;
	//dprintf(2, "\033[1;33mred: cmd %s\tinput = %d output = %d outfd = %d\033[0m\n", cmd->cmd[0], cmd->input, cmd->output, cmd->outfd);
	if (cmd->input == infile)
		err = dup2(cmd->infd, 0);
	else if (cmd->input == ipipe)
		err = dup2(redir->fdr_aux, 0);
	else if (cmd->input == stdi)
		err = dup2(redir->saved_std[0], 0);
	if (err == -1)
		print_errors(NULL);
	if (cmd->output == opipe)
		err = dup2(redir->fd_pipe[1], 1);
	else if (cmd->output == stdo)
		err = dup2(redir->saved_std[1], 1);
	else if (cmd->output == f_trunc || cmd->output == f_append)
		err = dup2(cmd->outfd, 1);
	if (err == -1)
		print_errors(NULL);
	if ((cmd->output == opipe || cmd->input == ipipe)
		&& (close(redir->fd_pipe[0]) == -1 || close(redir->fd_pipe[1]) == -1))
		return (print_errors(NULL));
	return (0);
}

int	exec_no_builtins(t_cmd *cmd, t_env *env, t_redir *redir, int flag)
{
	pid_t	pid;

	pid = -1;
	(void)env;
	if (flag)
	{
		pid = fork();
		if (pid == -1)
			return (print_errors(NULL));
	}
	if (pid == 0 || !flag)
	{
		redirections(cmd, redir);
		if (execve(cmd->cmd[0], cmd->cmd, NULL) == -1)
		{
			if (access(cmd->cmd[0], X_OK) == -1)
			{
				reset_std(redir, 2);
				printf("conxita: %s: command not found\n", cmd->cmd[0]);
			}
			else
				print_errors(NULL);
		}
		exit(127); //exit status 127
	}
	return (pid);
}

int	exec_cmd(t_cmd *cmd, t_env *env, t_redir *redir) // replace return (1) by a call to the function. It will return the exit code
{
	dprintf(2, "exec cmd: %s\n", cmd->cmd[0]);
	if (!ft_strncmp(cmd->cmd[0], "echo", 4))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "cd", 2))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 3))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "export", 6))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "unset", 5))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "env", 3))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "exit", 4))
		return (0);
	else if (cmd->len == 1)
		return (exec_no_builtins(cmd, env, redir, 1));
	else
		return (exec_no_builtins(cmd, env, redir, 0));
}

int	lets_execute(t_cmd *cmd, t_redir *redir, t_env *env, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	if (!cmd || !redir)
		return (print_errors(NULL));
	if (len == 1)
		return (exec_cmd(cmd, env, redir));
	while (++i < len)
	{
		if (pipe(redir->fd_pipe) == -1)
			return (print_errors(NULL));
		//execute heredoc
		if (cmd->heredoc)
		{
			if (dup2(redir->saved_std[0], 0) == -1)
				print_errors(NULL);
			continue ;
		}
		pid = fork();
		if (pid == 0)
			exec_cmd(&cmd[i], env, redir);
		if ((cmd[i].outfile && close(cmd[i].outfd) == -1)
			|| close(redir->fd_pipe[1]) == -1
			|| (redir->fdr_aux > 0 && close(redir->fdr_aux) == -1))
			return (print_errors(NULL));
		redir->fdr_aux = redir->fd_pipe[0];
	}
	return (pid);
}
