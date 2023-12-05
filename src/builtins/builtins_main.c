#include "../../conxita.h"

void	test_builtins(char *prompt, t_conxita *all)
{
	char		**s_prompt;
	char		*command;
	char		**args;

	s_prompt = ft_split(prompt, ' ');
	command = s_prompt[0];
	args = NULL;
	if (s_prompt[1] != NULL)
		args = &s_prompt[1];
	if (!ft_strncmp(command, "pwd", 4))
		all->exit = builtin_pwd();
	if (!ft_strncmp(command, "cd", 3))
		all->exit = builtin_cd(args, all->env);
	if (!ft_strncmp(command, "echo", 5))
		all->exit = builtin_echo(args);
	if (!ft_strncmp(command, "exit", 5))
		all->exit = builtin_exit(args, all);
}

int	handle_test_prompt(char *prompt, t_conxita *all)
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
	test_builtins(prompt, all);
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char		*prompt;
// 	t_conxita	all;

// 	(void)argc, (void)argv;
// 	all.env = env_to_lst(env);
// 	all.exit = 0;
// 	setup_signals();
// 	while ("test")
// 	{
// 		prompt = readline("blvilarn@TESTSHELL$ ");
// 		handle_test_prompt(prompt, &all);
// 	}
// }
