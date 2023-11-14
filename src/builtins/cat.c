#include "../../conxita.h"

//This was the function to print conxita and i've rescued it to act as cat
void	cat(char *file)
{
	int		fd;
	char	*line;

	if (!file)
		fd = 0;
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 2)
		cat(NULL);
	else
	{
		while (i < argc)
		{
			cat(argv[i]);
			i++;
		}
	}
	return (0);
}
