#include "../../conxita.h"

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
		return (-1);
	}
	return (0);
}

int	check_format(char *prompt)
{
	int	i;

	i = 0;
	if (check_o_quotes(prompt) == -1)
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
		printf("%s\n", "exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "", 2))
		return (-1);
	add_history(prompt);
	if (check_format(prompt))
		return (-1);
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
	return (0);
}
