#include "minishell.h"

static void	no_cmd_given(void)
{
	ft_leak(1234);
	write(STDERR_FILENO, "bimbo\n", 6);		//TODO I mean this should be impossible so you can put everything you want here really...
}

void	execution(t_cmd *cmd_list, t_shell *shell_data)
{
	int	cmd_c;

	save_close_restore_io(SAVE);
	/*
	if (check_4_heredoc(cmd_list) == -1)
		exit(EXIT_FAILURE);		//TODO Just print an error message and make sure setup_redir does not segvault.
	*/
	cmd_c = count_commands(cmd_list);
	if (cmd_c < 1)
		no_cmd_given();	
	else if (cmd_c == 1)
		single_cmd(cmd_list, shell_data);	//IN PROGRESS
	else
		mult_cmd(cmd_list, shell_data);	//IN PROGRESS
	save_close_restore_io(RESTORE);
}
