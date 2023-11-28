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
void	redirections(t_cmd *cmd, t_redir *redir)
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
	close(redir->fd_pipe[0]);
	close(redir->fd_pipe[1]);
	close(redir->saved_std[0]);
	close(redir->saved_std[1]);
}

void	exec_no_builtins(t_cmd *cmd, t_env *env)
{
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
	exit(127);
}

// replace return (1) by a call to the function. It will return the exit code
int	exec_cmd(t_cmd *cmd, t_env *env)
{
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (builtin_echo(cmd->cmd));
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
	else
		exec_no_builtins(cmd, env);
	return (0);
}

int	exec_multiple_cmd(t_cmd *cmd, t_env *env, t_redir *redir, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	while (++i < len)
	{
		if (pipe(redir->fd_pipe) == -1)
			return (print_errors(NULL));
		pid = fork();
		if (pid == 0)
		{
			redirections(&cmd[i], redir);
			exit(exec_cmd(&cmd[i], env));
		}
		close(cmd[i].outfd);
		close(redir->fd_pipe[1]);
		close(redir->fdr_aux);
		close(cmd->fd_hd);
		close(cmd->infd);
		redir->fdr_aux = redir->fd_pipe[0];
	}
	return (pid);
}

int	exec_one_cmd(t_cmd *cmd, t_env *env, t_redir *redir)
{
	int	fd[2];
	int	ret;

	fd[0] = dup(0);
	fd[1] = dup(1);
	redirections(cmd, redir);
	ret = exec_cmd(cmd, env);
	close(cmd->infd);
	close(cmd->outfd);
	return (ret);
}

int	lets_execute(t_cmd *cmd, t_redir *redir, t_env *env, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	if (!cmd || !redir)
		return (print_errors(NULL));
	if (len == 1 && is_builtin(cmd->cmd[0]))
		return (exec_one_cmd(cmd, env, redir));
	pid = exec_multiple_cmd(cmd, env, redir, len);
	close(redir->fdr_aux);
	return (pid);
}
