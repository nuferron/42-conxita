#include "../../conxita.h" 

int	get_arg_len(char *prompt, int i)
{
	int	len;

	len = 0;
	while (!ft_strchr("<>| ", prompt[i]))
	{
		if (prompt[i] == '\'')
			s_quote_len(prompt, &i, &len);
	}
	return (len);
}

void	handle_arg(char *prompt, t_oken *tokens, int *i, int *pos)
{
	int	len;

	len = get_arg_len(prompt, *i);
	while (!ft_strchr("<>| ", prompt[*i]))
	{

	}
}
