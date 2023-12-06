#include "../../conxita.h"


static void	check_number(unsigned long num, char *str)
{
	if (num == 0 || (num > 0 && ((num > LONG_MAX && str[0] != '-')
	|| (str[0] == '-' && num - 1 > LONG_MAX))))
	{
		ft_dprintf(2, "conxita: exit: %s: numeric argument required\n", str);
		exit(255);
	}
}
static void	check_digits(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] != '\0' && str[i] == '0')
		i++;
	if (str[i] == '\0')
		exit(0);
	if (len - i + (str[0] == '+' || str[0] == '-') <= 20)
		return ;
	ft_dprintf(2, "conxita: exit: %s: numeric argument required\n", str);
	exit(255);
}

static long long	is_valid_exit(char *str)
{
	int				i;
	unsigned long	num;
	int				neg;

	i = 0;
	num = 0;
	neg = 1;
	check_digits(str);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	check_number(num, str);
	return (num * neg);
}

int	builtin_exit(char **arg, t_conxita *all)
{
	int		argn;
	char	*str;

	//if (isatty(STDIN_FILENO))
	//{
	//	ft_dprintf(2, "EXIT: isatty\n");
	//	write(2, "exit\n", 5);
	//}
	argn = get_arg_number(arg);
	if (!argn)
	{
		system("leaks minishell");
		exit(all->exit);
	}
	str = ft_strtrim(arg[0], " ");
	if ((!ft_isnum(str) || !str) && ft_strncmp(str, "--", 3))
	{
		ft_dprintf(2, "conxita: exit: %s: numeric argument required\n", arg[0]);
		exit(255);
	}
	if (!ft_strncmp(str, "--", 3))
		exit(0);
	if (argn > 1)
	{
		ft_dprintf(2, "conxita: exit: too many arguments\n");
		free(str);
		return (1);
	}
	system("leaks minishell");
	exit((unsigned char)is_valid_exit(str));
}
