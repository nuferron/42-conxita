#include "../../conxita.h"

int	temporal_prompt_handle(char *prompt, t_env *env);

int	handle_prompt(char *prompt, t_env *env)
{
	t_oken	*tokens;
	t_cmd	*cmd;
	int		pid;

	if (temporal_prompt_handle(prompt, env) == -1)
		return (0);
	tokens = glorified_ft_split(ft_strtrim(prompt, " "), env);
	if (!tokens)
		return (0);
	/*int	i = 0;
	while (tokens[i].val)
		printf("handle prompt: %s\n", tokens[i++].val);*/
	cmd = token_to_cmd(tokens, env);
	pid = lets_execute(cmd, init_redir(), cmd_count(tokens, 1));
	if (pid == -1)
		exit(printf("handle prompt: lets execute is giving errors\n"));
		//return (-1);
	pid = ft_waitpid(pid);
	if (pid == -1)
		return (-1);
	free(prompt);
	return (0);
}

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
		printf("ERROR: Open quotes\n");
		return (1);
	}
	return (0);
}

int	temporal_prompt_handle(char *prompt, t_env *env)
{
	if (!prompt)
	{
		printf(LINE_DEL);
		printf("%s%s\n", search_env(env, "USER"), "@conxita$ exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "", 2))
		return (-1);
	add_history(prompt);
	if (check_o_quotes(prompt))
		return (-1);
	if (!ft_strncmp(prompt, "exit", 5) || !ft_strncmp(prompt, "make", 4))
	{
		free(prompt);
		printf("%s\n", "exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "conxita", 8))
		print_conxita();
	return (0);
}
