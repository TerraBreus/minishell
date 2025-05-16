int	single_command(t_cmd *cmd_list, t_custom_envp *t_envp)
{
//Setup redirection.
	if (set_redirection(cmd_list->redirection) == -1)
		return (-1);
	if (exec_cmd(cmd_list->argv, t_envp) == -1)
		return (-1);
	return (0);
}
