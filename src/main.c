#include "../inc/minishell.h"

char	*bash_read_line(void)
{
	char	*str;

	return (str);
}

void	bash_loop(void)
{
	char	*line;

	while (1)
	{
		printf(MINISHELL);
		line = bash_read_line();
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		bash_loop();
	return (0);
}
