#include "../inc/minishell.h"

void	bash_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline(MINISHELL);
		if (!line)
			break ;
		else if (line[0] == '\0')
			free(line);
		else
		{
			printf("%s\n", line);
			add_history(line);
			free(line);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		bash_loop();
	return (0);
}
