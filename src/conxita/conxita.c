#include "../../conxita.h"

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	*prompt_text;

	(void)argv;
	if (argc > 1)
		return (printf("Too many arguments\n"));
	print_conxita();
	setup_signals();
	while ("Conxita")
	{
		prompt_text = ft_strjoin(getenv("USER"), "@conxita$ ");
		prompt = readline(prompt_text);
		free(prompt_text);
		handle_prompt(prompt, env);
	}
	return (0);
}
