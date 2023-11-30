#include "../../conxita.h"

<<<<<<< HEAD
=======
int	temporal_prompt_handle(char *prompt, t_env *env);

int	handle_prompt(char *prompt, t_conxita *all)
{
	int		pid;

	if (temporal_prompt_handle(prompt, all->env) == -1)
	{
		all->exit = 258;
		return (-1);
	}
	all->token = glorified_ft_split(ft_strtrim(prompt, " "), all);
	if (!all->token)
		return (0);
	all->cmd = token_to_cmd(all, cmd_count(all->token, 0) + 1);
	if (!all->cmd)
	{
		all->exit = 258;
		return (-1);
	}
	all->redir = init_redir();
	printf("cmd %s\nint %d\tout %d\n", all->cmd->cmd[0], all->cmd->input, all->cmd->output);
	printf("cmd %s\nint %d\tout %d\n", all->cmd->cmd[1], all->cmd->input, all->cmd->output);
	pid = lets_execute(all, all->cmd->len);
	if (pid > 0)
		all->exit = ft_waitpid(pid, all->cmd->len);
	else if (pid == 0)
		all->exit = 0;
	free(all->redir);
	free_the_tokens(all->token);
	free_cmd(all->cmd);
	free(prompt);
	return (0);
}

>>>>>>> main
int	check_o_quotes(char *prompt)
{
	int		i;
	bool	o_simple;
	bool	o_double;

	i = 0;
	o_simple = FALSE;
	o_double = FALSE;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && !o_double)
			b_invert(&o_simple);
		if (prompt[i] == '"' && !o_simple)
			b_invert(&o_double);
		i++;
	}
	if (o_simple || o_double)
	{
		ft_dprintf(2, "ERROR: Open quotes\n");
<<<<<<< HEAD
		return (-1);
	}
	return (0);
}

int	check_format(char *prompt)
{
	int	i;

	i = 0;
	if (check_o_quotes(prompt) == -1)
=======
>>>>>>> main
		return (-1);
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '|')
		{
			if (prompt[i + 1] == '|')
			{
				dprintf(2, "ERROR: double pipe detected\n");
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	check_input(char *prompt)
{
	if (!prompt)
	{
<<<<<<< HEAD
		printf("%s\n", "exit");
=======
		free_env(env);
		printf("exit\n");
		system("leaks conxita");
>>>>>>> main
		exit(0);
	}
	if (!ft_strncmp(prompt, "", 2))
		return (-1);
	add_history(prompt);
	if (check_format(prompt))
		return (-1);
<<<<<<< HEAD
	return (0);
}

int	handle_prompt(char *prompt, t_conxita *all)
{
	int		pid;
	t_redir	*redir;

	if (check_input(prompt) == -1)
		return (0);
	all->token = glorified_ft_split(ft_strtrim(prompt, " "), all);
	if (!all->token)
		return (0);
	all->cmd = token_to_cmd(all->token, all->env, cmd_count(all->token, 0) + 1);
	redir = init_redir();
	if (!redir || !all->cmd)
		return (-1);
	pid = lets_execute(all->cmd, redir, all->env, all->cmd->len);
	if (pid > 0)
		all->exit = ft_waitpid(pid, all->cmd->len);
	free(prompt);
=======
	if (!ft_strncmp(prompt, "exit", 5) || !ft_strncmp(prompt, "make", 4))
	{
		free_env(env);
		free(prompt);
		printf("%s\n", "exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "conxita", 8))
		print_conxita();
>>>>>>> main
	return (0);
}
