#include "../../conxita.h"

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	*prompt_text;

	(void)argv;
	(void)env;
	if (argc > 1)
		return (printf("Too many arguments\n"));
	print_conxita();
	setup_signals();
	while ("Conxita")
	{
		prompt_text = ft_strjoin(getenv("USER"), "@conxita$ ");
		prompt = readline(prompt_text);
		free(prompt_text);
		write(2, "main loop\n", 10);
		handle_prompt(prompt, env);
		write(2, "main loop 2\n", 12);
	}
	return (0);
}
