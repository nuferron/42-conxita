#include "../conxita.h"

int	errors(t_mateu *mateu, char *str)
{
	printf("conxita: ");
	perror(str);
}
