#include "../../conxita.h"

int	reset_std(t_redir *redir, int which)
{
	if (which == 0 || which == 2)
	{
		if (dup2(redir->saved_std[0], 0) == -1)
			return (print_errors("WTFFF"));
	}
	if (which == 1 || which == 2)
	{
		if (dup2(redir->saved_std[1], 1) == -1)
			return (print_errors("adeu"));
	}
	return (0);
}

/*Redirects the file desccriptors according with the input*/
int	redirections(t_cmd *cmd, t_redir *redir)
{
	int	err;

	err = 0;
	if (cmd->fd_hd != -1)
		err = dup2(cmd->fd_hd, 0);
	else if (cmd->input == infile)
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
	close(redir->saved_std[0]);
	close(redir->saved_std[1]);
	return (0);
}

int	exec_no_builtins(t_cmd *cmd, t_env *env, t_redir *redir, int flag)
{
	pid_t	pid;

	pid = -1;
	if (flag)
	{
		pid = fork();
		if (pid == -1)
			return (print_errors(NULL));
	}
	if (pid == 0 || !flag)
	{
		redirections(cmd, redir);
		if (execve(cmd->cmd[0], cmd->cmd, env_to_mat(env, 0)) == -1)
		{
			if (access(cmd->cmd[0], X_OK) == -1)
			{
				ft_putstr_fd("conxita: ", 2);
				ft_putstr_fd(cmd->cmd[0], 2);
				ft_putstr_fd(": command not found\n", 2);
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
	//dprintf(2, "exec cmd: %s\n", cmd->cmd[0]);
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
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
	int		ret;

	i = -1;
	if (!cmd || !redir)
		return (print_errors(NULL));
	if (len == 1)
	{
		ret = exec_cmd(cmd, env, redir);
		close(cmd->infd);
		close(cmd->outfd);
		return (ret);
	}
	while (++i < len)
	{
		if (pipe(redir->fd_pipe) == -1)
			return (print_errors(NULL));
		pid = fork();
		if (pid == 0)
			exec_cmd(&cmd[i], env, redir);
		if ((cmd[i].outfile && close(cmd[i].outfd) == -1)
			|| close(redir->fd_pipe[1]) == -1
			|| (redir->fdr_aux > 0 && close(redir->fdr_aux) == -1))
		{
			close(redir->fdr_aux);
			return (print_errors(NULL));
		}
		redir->fdr_aux = redir->fd_pipe[0];
		close(cmd->fd_hd);
		close(cmd->infd);
	}
	close(redir->fdr_aux);
	return (pid);
}
