#include "minishell.h"

int	check_4_heredoc(t_shell *shell, t_cmd *cmd_list)
{
	t_redir	*temp;

	while (cmd_list != NULL)
	{
		temp = cmd_list->redirection;
		while (temp != NULL)
		{
			if (temp->type == HEREDOC)
			{
				if (setup_heredoc(shell, temp) == -1)
					return (-1);					//TODO heredoc handler failed.
			}
			temp = temp->next; 
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

