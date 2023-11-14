#include "../../conxita.h"

void	*free_the_tokens(t_oken *tokens)
{
	int	i;

	i = 0;x`
	while (tokens[i].val)
	{
		free(tokens[i].val);
		i++;
	}
	free(tokens);
	return (NULL);
}
