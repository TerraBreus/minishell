#include "minishell.h"

static void	no_cmd_given(void)
{
	write(STDERR_FILENO, "bimbo\n", 6);		//TODO I mean this should be impossible so you can put everything you want here really...
}

void	execution(t_cmd *cmd_list, t_shell *shell_data)
{
	int	cmd_c;

	save_close_restore_io(SAVE);
	cmd_c = count_commands(cmd_list);
	if (cmd_c < 1)
		no_cmd_given();	
	else if (cmd_c == 1)
		single_cmd(cmd_list, shell_data);	//IN PROGRESS
	else
		mult_cmd(cmd_list, shell_data);	//IN PROGRESS
	save_close_restore_io(RESTORE);
}
