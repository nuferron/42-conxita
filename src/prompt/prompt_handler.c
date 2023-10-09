#include "../../conxita.h"

int	temporal_prompt_handle(char *prompt);

t_parsing	_get_quotes(char *prompt)
{
	int			i;
	t_parsing	_quotes;

	i = 0;
	_quotes.o_simple = FALSE;
	_quotes.o_double = FALSE;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && !_quotes.o_double)
			b_invert(&(_quotes.o_simple));
		if (prompt[i] == '\"' && !_quotes.o_simple)
			b_invert(&(_quotes.o_double));
		i++;
	}
	return (_quotes);
}

int	handle_prompt(char *prompt)
{
	temporal_prompt_handle(prompt);
	glorified_ft_split(ft_strtrim(prompt, " "));
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
		return(1);
	add_history(prompt);
	if (check_o_quotes(prompt))
		return (0);
	if (!ft_strncmp(prompt, "exit", 5))
	{
		free(prompt);
		printf("%s\n", "exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "conxita", 8))
		print_conxita();
	else if (prompt)
		printf("%s\n", prompt);
	return (0);
}
