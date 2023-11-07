#include "../../conxita.h"

char	*ft_strtrim_free(char *s1, char *set)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(s1, set);
	free(s1);
	return (trimmed_str);
}
