#include "../../conxita.h"

void	handle_single(char *prompt, t_comp *comps, int *i, int *comp_i)
{
	int	j;
	int	len;

	j = 0;
	write_single(comps, i, '\'', s_quote);
	(*i)++;
	(*comp_i)++;
	if (prompt[*i] && prompt[*i] != '\'')
	{
		len = get_word_len(prompt, *i, "'");
		comps[*comp_i].val = ft_calloc(len + 1, sizeof(char));
		while (!ft_strchr("'", prompt[*i]))
		{
			comps[*comp_i].val[j] = prompt[*i];
			(*i)++;
		}
		(*comp_i)++;
	}
	write_single(comps, i, '\'', s_quote);
}

// static void	handle_double(char *prompt, t_comp comps, int *i, int *comp_i)
// {
// 	"code goes here";
// }