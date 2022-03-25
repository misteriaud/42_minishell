#include <minishell.h>

int	history()
{

	if (access(".minishell_history", F_OK))
	{
		open(".minishell_history", O_RDWR | O_APPEND | O_CREAT, 0777);
		write(1, "Creating history file :P\n", 24);
	}



	return (0);
}
