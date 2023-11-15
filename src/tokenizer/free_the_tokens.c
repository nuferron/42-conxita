#include "../../conxita.h"

void	*free_the_tokens(t_oken *tokens)
{
	int			i;

	i = 0;
	while (tokens && tokens[i].val)
	{
		free(tokens[i].val);
		i++;
	}
	if (tokens)
		free(tokens);
	return (NULL);
}
