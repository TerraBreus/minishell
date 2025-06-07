#include "minishell.h"

static int	check_infile_perm(char *filename)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == 0)
			return (0);
		perror("Insufficient permissions:");
		return (-1);
	}
	perror("Infile not found");
	return (-1);
}
static int	check_outfile_perm(char *filename)
{
	if (access(filename, F_OK) == 0)
		{
			if (access(filename, W_OK) == 0)
				return (0);
			perror("Insufficient permissions:");
			return (-1);
		}
		return (0);
}
int	check_file_permissions(char *filename, t_redir_type type)
{
	if (type == APPEND || type == OUT)
		return (check_outfile_perm(filename));
	else if (type == IN)
		return (check_infile_perm(filename));
	write(2, "check_file_permission\n", 24);
	return (-1);
}
