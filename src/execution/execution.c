#include "../../conxita.h"

void	exec_no_builtins(t_cmd *cmd, t_env *env)
{
	if (!cmd->cmd)
		exit(0);
	if (execve(cmd->cmd[0], cmd->cmd, env_to_mat(env, 0)) == -1)
	{
		if (access(cmd->cmd[0], X_OK) == -1)
			ft_dprintf(2, "conxita: %s: command not found\n", cmd->cmd[0]);
		else
			print_errors("exec no buil");
	}
	exit(127);
}

// replace return (1) by a call to the function. It will return the exit code
int	exec_cmd(t_cmd *cmd, t_conxita *all)
{
	if (!cmd->cmd)
		return (0);
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (builtin_echo(&(cmd->cmd[0])));
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (builtin_cd(&(cmd->cmd[1]), all->env));
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (builtin_pwd(&(cmd->cmd[1])));
	else if (!ft_strncmp(all->cmd->cmd[0], "export", 7))
		return (0);
	else if (!ft_strncmp(all->cmd->cmd[0], "unset", 6))
		return (0);
	else if (!ft_strncmp(all->cmd->cmd[0], "env", 4))
		return (0);
	else if (!ft_strncmp(all->cmd->cmd[0], "exit", 5))
		return (builtin_exit(&(cmd->cmd[1]), all));
	else
		exec_no_builtins(cmd, all->env);
	return (0);
}

int	exec_multiple_cmd(t_conxita *all, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	while (++i < len)
	{
		if (pipe(all->redir->fd_pipe) == -1)
			exit(-print_errors(NULL));
		pid = fork();
		if (pid == 0)
		{
			redirections(&(all->cmd[i]), all->redir);
			exit(exec_cmd(&(all->cmd[i]), all));
		}
		close(all->cmd[i].outfd);
		close(all->redir->fd_pipe[1]);
		close(all->redir->fdr_aux);
		close(all->cmd->fd_hd);
		close(all->cmd->infd);
		all->redir->fdr_aux = all->redir->fd_pipe[0];
	}
	return (pid);
}

int	exec_one_builtin(t_conxita *all)
{
	int	fd[2];
	int	ret;

	fd[0] = dup(0);
	fd[1] = dup(1);
	redirections(all->cmd, all->redir);
	ret = exec_cmd(all->cmd, all);
	close(all->cmd->infd);
	close(all->cmd->outfd);
	if (dup2(fd[0], 0) == -1)
		exit(-print_errors(NULL));
	if (dup2(fd[1], 1) == -1)
		exit(-print_errors(NULL));
	return (ret);
}

int	lets_execute(t_conxita *all, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	if (!all->cmd->cmd)
		return (0);
	if (len == 1 && is_builtin(all->cmd->cmd[0]))
		return (exec_one_builtin(all));
	pid = exec_multiple_cmd(all, len);
	close(all->redir->fdr_aux);
	close(all->cmd->fd_hd);
	return (ft_waitpid(pid, len));
}
