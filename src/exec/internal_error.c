#include "minishell.h"

int	internal_error()
{
	perror("Internal error occured.");
	return (INTERNAL_ERROR);
}


