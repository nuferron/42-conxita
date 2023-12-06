#include "../../conxita.h"

static void	add_shlvl(t_env *env)
{
	char	*new_shlvl;
	t_env	*shlvl;

	shlvl = search_env(env, "SHLVL");
	if (shlvl == NULL)
		return ;
	new_shlvl = ft_itoa(ft_atoi(shlvl->value) + 1);
	free(shlvl->value);
	shlvl->value = new_shlvl;
}

void	term_init(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
	all.env = env_to_lst(env);
	all.exit = 0;
	add_shlvl(all.env);
	term_init();
	while ("Conxita")
	{
		set_signals_interactive();
		prompt_text = ft_strjoin(search_env(all.env, "USER")->value, "@conxita$ ");
		prompt = readline(prompt_text);
		free(prompt_text);
		handle_prompt(prompt, &all);
		//free_all(&all);
		//free(prompt);
		set_signals_noninteractive();
	}
	return (0);
}
