#include "../../conxita.h"

// int	main(int argc, char **argv, char **env)
// {
// 	char		*prompt;
// 	char		*prompt_text;
// 	t_conxita	all;

// 	(void)argv;
// 	if (argc > 1)
// 		return (printf("Too many arguments\n"));
// 	print_conxita();
// 	setup_signals();
// 	all.env = env_to_lst(env);
// 	all.exit = 0;
// 	while ("Conxita")
// 	{
// 		prompt_text = ft_strjoin(search_env(all.env, "USER"), "@conxita$ ");
// 		prompt = readline(prompt_text);
// 		free(prompt_text);
// 		handle_prompt(prompt, &all);
// 	}
// 	return (0);
// }
