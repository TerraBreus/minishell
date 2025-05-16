#include "minishell.h"

int	chain_of_commands(t_cmd *cmd_list, t_custom_env *t_envp)
{
	int	cmd_c;
	int	error_check;

	//TODO
	//print some error message saying there must have been prior malloc failure.
	if (cmd_list == NULL || t_envp == NULL)
		return (-1);

	cmd_c = count_commands(cmd_list);
	
	//COPY STDIN and STDOUT to restore at the end.
	save_or_restore_io(SAVE);	//TODO

	//MULTIPLE COMMANDS WILL CREATE A PIPE STRUCTURE. SINGLE_COMMAND WONT.
	if (cmd_c == 1)
		error_check = single_command(cmd_list, t_envp);
	else
		error_check = multiple_commands(cmd_list, t_envp);	//TODO

	//RESTORE THE STDIN AND STDOUT TO ALLOW FOR NEW PROMPT AND USER INPUT. 
	save_or_restore_IO(RESTORE);
	return (error_check);
}
