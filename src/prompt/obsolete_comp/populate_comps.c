#include "../../conxita.h"

//? Cases to handle
//* Whitespaces
//! Single quotes
//! Double quotes
//* Other text

void	write_single(t_comp *comps, int *i, char c, enum e_arg_type type)
{
	comps[*i].val = (char *)ft_calloc(2, sizeof(char));
	if (!comps[*i].val)
		return ; //!FREE ALL
	comps[*i].val[0] = c;
	comps[*i].type = type;
	(*i)++;
}

int	get_word_len(char *prompt, int i, char *delimiters)
{
	int	len;

	len = 0;
	while (!ft_strchr(delimiters, prompt[i + len]))
		len++;
	return (len);
}

void	write_word(char *prompt, t_comp *comps, int	*i, int *comp_i)
{
	int	j;
	int	len;

	j = 0;
	len = get_word_len(prompt, *i, "'\" ");
	comps[*comp_i].val = (char *)ft_calloc(len + 1, sizeof(char));
	if (!comps[*comp_i].val)
		return ; //!free all
	while (!ft_strchr("'\" ", prompt[*i]))
	{
		comps[*comp_i].val[j] = prompt[*i];
		(*i)++;
		j++;
	}
	(*comp_i)++;
}

void	populate_comps(char *prompt, t_comp *comps)
{
	int		i;
	int		comp_i;

	i = 0;
	comp_i = 0;
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			write_single(comps, &comp_i, ' ', spc);
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'' || prompt[i] == '"') //! remove "
			handle_single(prompt, comps, &i, &comp_i);
		if (!ft_strchr("'\" ", prompt[i]))
			write_word(prompt, comps, &i, &comp_i);
	}
}
