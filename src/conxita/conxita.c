#include "../../conxita.h"

static void	add_shlvl(t_env *env)
{
	char	*new_shlvl;
	t_env	*shlvl;

	shlvl = search_t_env(env, "SHLVL");
	if (shlvl == NULL)
		return ;
	new_shlvl = ft_itoa(ft_atoi(shlvl->value) + 1);
	free(shlvl->value);
	shlvl->value = new_shlvl;
}

int	main(int argc, char **argv, char **env)
{
	char		*prompt;
	char		*prompt_text;
	t_conxita	all;

	(void)argv;
	if (argc > 1)
		return (printf("Too many arguments\n"));
	print_conxita();
	setup_signals();
	all.env = env_to_lst(env);
	all.exit = 0;
	add_shlvl(all.env);
	while ("Conxita")
	{
		prompt_text = ft_strjoin(search_env(all.env, "USER"), "@conxita$ ");
		all.token = NULL;
		all.cmd = NULL;
		while ("Conxita")
		{
			if (search_env(all.env, "USER")->value != NULL)
				prompt_text = ft_strjoin(search_env(all.env, "USER")->value,
				"@conxita$ ");
			else
				prompt_text = ft_strdup("[unknown]@conxita$ ");
			prompt = readline(prompt_text);
			if (!prompt)
			{
				if (isatty(STDIN_FILENO))
					write(2, "exit\n", 6);
				exit (all.exit);
			}
			free(prompt_text);
			handle_prompt(prompt, &all);
			//free_all(&all);
			free(prompt);
		}
	return (0);
}
