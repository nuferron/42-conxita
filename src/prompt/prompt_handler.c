#include "../../conxita.h"

static int	prompt_preprocessor(char *prompt, t_conxita *all);

int	handle_prompt(char *prompt, t_conxita *all)
{
	if (!ft_strncmp(prompt, "", 2))
		return (-1);
	if (prompt_preprocessor(prompt, all->env) < 0)
	{
		all->exit = 258;
		return (-1);
	}
	all->token = glorified_ft_split(ft_strtrim(prompt, " "), all);
	if (!all->token)
		return (0);
	if (!token_to_cmd(all, cmd_count(all->token, 0) + 1))
		return (-1);
	all->redir = init_redir();
	all->exit = lets_execute(all, all->cmd->len);
	return (0);
}

static int	check_prompt_errors(char *prompt)
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
		if (prompt[i] == '|' && prompt[i + 1] == '|')
			return (ft_dprintf(2, "conxita: error: double pipe\n"), -1);
		i++;
	}
	if (o_simple || o_double)
	{
		ft_dprintf(2, "conxita: error: open quotes\n");
		return (-1);
	}
	return (0);
}

static int	prompt_preprocessor(char *prompt, t_env *env)
{
	if (!prompt)
	{
		free_env(all->env);
		printf("exit\n");
		system("leaks minishell");
		exit(0);
	}
	add_history(prompt);
	if (check_prompt_errors(prompt) == -1)
		return (-1);
	return (0);
}
