
/*
static void	no_cmd_given(void)
{
	//print error message.
}
*/

#include "minishell.h"

void	execution(t_cmd *cmd_list, t_shell *shell_data)
{
	int	cmd_c;

	save_close_restore_io(SAVE);
	cmd_c = count_commands(cmd_list);
	if (cmd_c < 2)					//TODO Remove when you have more options
		return ;
	/*
	if (cmd_c < 1)
		no_cmd_given();				//TODO what to do when NULL pointer given?
	else if (cmd_c == 1)
		;//single_command(cmd_list, shell_data);	//TODO
	else
		; //mult_commands(cmd_list, shell_data);	//IN PROGRESS
	*/
	mult_cmd(cmd_list, shell_data);
	save_close_restore_io(RESTORE);

}
