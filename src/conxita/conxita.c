#include "../../conxita.h"

char	*get_prompt(t_conxita *all)
{
	char	*prompt;
	char	*str;
	t_env	*user;

	user = search_env(all->env, "USER");
	if (user != NULL && *user->value)
		str = ft_strjoin(user->value, "@conxita$ ");
	else
		str = ft_strdup("[unknown]@conxita$ ");
	prompt = readline(str);
	if (!prompt)
	{
		if (isatty(STDIN_FILENO))
		{
			printf(LINE_DEL);
			printf("%s %s\n", str, "exit");
		}
		exit(all->exit);
	}
	free(str);
	return (prompt);
}

static void	free_all(t_conxita *all)
{
	free_the_tokens(all->token);
	free_cmd(all->cmd);
	free(all->redir);
	all->cmd = NULL;
	all->token = NULL;
	all->redir = NULL;
}

static void	init_all(t_conxita *all, char **env)
{
	all->cmd = NULL;
	all->env = env_to_lst(env);
	all->token = NULL;
	all->redir = NULL;
	all->exit = 0;
	add_shlvl(all->env);
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
	t_conxita	all;

	(void)argv;
	if (argc > 1)
		return (printf("Too many arguments\n"));
	//print_conxita();
	init_all(&all, env);
	term_init();
	while ("Conxita")
	{
		set_signals_interactive();
		prompt = get_prompt(&all);
		set_signals_noninteractive();
		handle_prompt(prompt, &all);
		free_all(&all);
		free(prompt);
	}
	return (0);
}
