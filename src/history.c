#include <minishell.h>

int	history()
{
	if (access(".minishell_history", F_OK))
	{
		open(".minishell_history", O_RDWR | O_APPEND | O_CREAT, 0777);
		write(1, "\U0001F4AD ", 5);
		write(1, "Creating history file :P\n", 25);
	}
	return (0);
}
