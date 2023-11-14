#include "../../conxita.h"

int	temporal_prompt_handle(char *prompt);

int	handle_prompt(char *prompt, char **env)
{
	t_oken	*tokens;
	int		prot;

	if (temporal_prompt_handle(prompt) == -1)
		return (0);
	tokens = glorified_ft_split(ft_strtrim(prompt, " "), env);

	int	k = 0;
	while (k < 5)
	{
		printf("han_prompt: tok %s type %d\n", tokens[k].val, tokens[k].type);
		k++;
	}

	prot = lets_execute(token_to_cmd(tokens), init_redir(), arg_len(tokens, 1));
	if (prot == -1)
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
		return(1);
	}
	return (0);
}

int	temporal_prompt_handle(char *prompt)
{
	if (!prompt)
	{
		printf(LINE_DEL);
		printf("%s%s\n", getenv("USER"), "@conxita$ exit");
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
	else if (prompt)
		printf("\033[1;36mtemporal prompt handler: %s\033[0m\n", prompt); // why this? It's printing the input
	return (0);
}
