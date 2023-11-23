#include "../../conxita.h"

// int	main(int argc, char **argv, char **env)
// {
// 	char	*prompt;
// 	char	*prompt_text;
// 	t_env	*tenv;

// 	(void)argv;
// 	if (argc > 1)
// 		return (printf("Too many arguments\n"));
// 	print_conxita();
// 	setup_signals();
// 	tenv = env_to_lst(env);
// 	while ("Conxita")
// 	{
// 		prompt_text = ft_strjoin(search_env(tenv, "USER"), "@conxita$ ");
// 		prompt = readline(prompt_text);
// 		free(prompt_text);
// 		handle_prompt(prompt, tenv);
// 	}
// 	return (0);
// }
