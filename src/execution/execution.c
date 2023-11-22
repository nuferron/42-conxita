#include "../../conxita.h"

int	exec_no_builtins(t_cmd *cmd, t_env *env, int flag)
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
		if (execve(cmd->cmd[0], cmd->cmd, NULL) == -1)
		{
			if (access(cmd->cmd[0], X_OK) == -1)
				printf("conxita: %s: command not found\n", cmd->cmd[0]);
			else
				print_errors(NULL);
		}
	}
	return (127);
}

int	exec_cmd(t_cmd *cmd, t_env *env) // replace return (1) by a call to the function. It will return the exit code
{
	if (!ft_strncmp(cmd->cmd[0], "echo ", 5))
		return (1);
	else if (!ft_strncmp(cmd->cmd[0], "cd ", 3))
		return (1);
	else if (!ft_strncmp(cmd->cmd[0], "pwd ", 4))
		return (1);
	else if (!ft_strncmp(cmd->cmd[0], "export ", 7))
		return (1);
	else if (!ft_strncmp(cmd->cmd[0], "unset ", 6))
		return (1);
	else if (!ft_strncmp(cmd->cmd[0], "env ", 4))
		return (1);
	else if (!ft_strncmp(cmd->cmd[0], "exit ", 5))
		return (1);
	else if (cmd->len == 1)
		return (exec_no_builtins(cmd, env, 1));
	else
		return (exec_no_builtins(cmd, env, 0));
}

/*Redirects the file desccriptors according with the input*/
int	redirections(t_cmd *cmd, t_redir *redir)
{
	int	err;

	//dprintf(2, "red: cmd %s\tinput = %d output = %d\n", cmd->cmd[0], cmd->input, cmd->output);
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

int	lets_execute(t_cmd *cmd, t_redir *redir, t_env *env, int len)
{
	pid_t	pid;
	int		i;
	int		err;

	i = -1;
	if (!cmd || !redir)
		return (print_errors(NULL));
	if (len == 1)
		return (exec_cmd(cmd, env));
	while (++i < len)
	{
		if (pipe(redir->fd_pipe) == -1)
			return (print_errors(NULL));
		if (cmd->heredoc)
		{
			if (dup2(redir->saved_std[0], 0) == -1)
				print_errors(NULL);
			continue ;
		}
		//execute heredoc
		pid = fork();
		if (pid == 0)
		{
			redirections(&cmd[i], redir);
			err = exec_cmd(&cmd[i], env);
		}
		if ((cmd[i].outfile && close(cmd[i].outfd) == -1)
			|| close(redir->fd_pipe[1]) == -1
			|| (redir->fdr_aux > 0 && close(redir->fdr_aux) == -1))
			return (print_errors(NULL));
		redir->fdr_aux = redir->fd_pipe[0];
	}
	return (pid);
}
