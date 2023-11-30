#include "../../conxita.h"

void	test_builtins(char *prompt, t_env *env)
{
	char	**s_prompt;
	char	*command;
	char	**args;

	s_prompt = ft_split(prompt, ' ');
	command = s_prompt[0];
	args = NULL;
	if (s_prompt[1] != NULL)
		args = &s_prompt[1];
	if (!ft_strncmp(command, "pwd", 4))
		builtin_pwd(args);
	if (!ft_strncmp(command, "cd", 3))
		builtin_cd(args, env);
	if (!ft_strncmp(command, "echo", 5))
		builtin_echo(args);
}

int	handle_test_prompt(char *prompt, t_env *env)
{
	if (!prompt)
	{
		printf(LINE_DEL);
		printf("%s\n", "blvilarn@TESTSHELL$ ");
		exit(0);
	}
	if (!ft_strncmp(prompt, "", 2))
		return (-1);
	add_history(prompt);
	if (!ft_strncmp(prompt, "make", 4))
	{
		free(prompt);
		printf("%s\n", "exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "conxita", 8))
		print_conxita();
	test_builtins(prompt, env);
	return (0);
}

/*
int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	t_env	*lst_env;

	(void)argc, (void)argv;
	lst_env = env_to_lst(env);
	setup_signals();
	while ("test")
	{
		prompt = readline("blvilarn@TESTSHELL$ ");
		handle_test_prompt(prompt, lst_env);
	}
}
*/