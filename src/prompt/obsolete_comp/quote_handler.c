#include "../../conxita.h"

void	handle_single(char *prompt, t_comp *comps, int *i, int *comp_i)
{
	int	j;
	int	len;

	j = 0;
	printf("comp_i: %i\n", *comp_i);
	write_single(comps, comp_i, '\'', s_quote);
	(*i)++;
	if (prompt[*i] && prompt[*i] != '\'')
	{
		len = get_word_len(prompt, *i, "'");
		comps[*comp_i].val = ft_calloc(len + 1, sizeof(char));
		while (prompt[*i] != '\'')
		{
			comps[*comp_i].val[j] = prompt[*i];
			(*i)++;
			j++;
		}
		(*comp_i)++;
	}
	printf("%c\n", prompt[*i]);
	write_single(comps, comp_i, '\'', s_quote);
}

// static void	handle_double(char *prompt, t_comp comps, int *i, int *comp_i)
// {
// 	"code goes here";
// }