#include "minishell.h"

int	close_and_return(int in, int out)
{
	close(in);
	close(out);
	return (-1);
}

int	save_or_restore_io(int restore_or_save)
{
	static int	copy_in;
	static int	copy_out;

	if (restore_or_save == SAVE)
	{
		copy_in = dup(STDIN_FILENO);
		copy_out = dup(STDOUT_FILENO);
		return (0);
	}
	else if (restore_or_save == RESTORE)
	{
		if (dup2(copy_in, STDIN_FILENO) == -1)
			return (close_and_return(copy_in, copy_out));
		if (dup2(copy_out, STDOUT_FILENO) == -1)
			return (close_and_return(copy_in, copy_out));
		close(copy_in);
		close(copy_out);
		return (0);
	}
	else if(restore_or_save == CLOSE)
	{
		close(copy_in);
		close(copy_out);
		return (0);
	}
	else 
		return (-1);
}
