#include "../../conxita.h"

int	exec_no_builtins(t_cmd *cmd, t_env *env, int flag)
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
	if (!ft_strncmp(cmd->&(cmd[1]), "echo ", 5))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "cd ", 3))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "pwd ", 4))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "export ", 7))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "unset ", 6))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "env ", 4))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "exit ", 5))
		return (1);
	else if (cmd->len == 1)
		return (exec_no_builtins(cmd, env, 1));
	else
		return (exec_no_builtins(cmd, env, 0));
}

int	redirections(t_cmd *cmd, t_redir *redir)
{
	
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
		pid = fork();
		if (pid == 0)
		{
			redirections(cmd, redir);
			err = exec_cmd(cmd, env);
		}
		if ((cmd[i].outfile && close(cmd[i].outfd) == -1)
			|| close(redir->fd_pipe[1]) == -1
			|| (redir->fdr_aux > 0 && close(redir->fdr_aux) == -1))
			return (print_errors(NULL));
		redir->fdr_aux = redir->fd_pipe[0];
	}
}
