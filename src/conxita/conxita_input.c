#include "../../conxita.h"

int	skip_sp(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' ')))
		i--;
	return (i);
}

int	checking_chevrons(char *input, int i)
{
	if (i && input[i] == '<' && input[i - 1] == '>')
		return (0);
	else if (i && input[i] == '>' && input[i - 1] == '<')
		return (0);
	else if (i > 1 && input[i] == '>'
		&& input[i - 1] == '>' && input[i - 2] == '>')
		return (0);
	else if (i > 1 && input[i] == '<'
		&& input[i - 1] == '<' && input[i - 2] == '<')
		return (0);
	return (1);
}

int	valid_input(char *input)
{
	int			i;
	t_parsing	parse;

	i = 0;
	parse.o_simple = 0;
	parse.o_double = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' && parse.o_simple)
			parse.o_simple = 0;
		else if (input[i] == '\'' && !parse.o_simple)
			parse.o_simple = 1;
		else if (input[i] == '\"' && parse.o_double)
			parse.o_double = 0;
		else if (input[i] == '\"' && !parse.o_double)
			parse.o_double = 1;
		else if (!checking_chevrons(input, i))
			return (0);
		i++;
	}
	i = skip_sp(input);
	if (i == -1 || input[i] == '>' || input[i] == '<' || input[i] == '|'
		|| parse.o_simple || parse.o_double)
		return (0);
	return (1);
}
/*
void	test(char *str)
{
	int	argc;

	argc = valid_input(str);
	if (argc == 1)
		printf("|%s| Is a valid input\n", str);
	else
		printf("|%s| Is definitely NOT a valid input\n", str);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		argv[0] = ft_strjoin(argv[0], argv[i]);
		i++;
	}
	test("hola>>>");
	test("hola<>a");
	test("hola<");
	test("hola >>");
	test("hola >> ");
	test("hola | ");
	test("hola |");
	test("hola >< a");
	test("             ");
	test("\'hola");
	test("hola\'");
	test("\"hola");
	test("hola\"");
	test("a            ");
	test(" a > a | a");
	test("a>a|a");
	test("a>>a<<a");
	return (0);
}*/
