//This function is going to create a pipe structure for us.
//It returns -1 if malloc allocation has failed.

int	init_pipe(t_pipe **plumb_box, t_cmd *c)
{

	// Create a pipe structure if we are
	if (*plumb_box == NULL && c->next != NULL)
	{
		plumb_box = (t_pipe *)malloc(sizeof(t_pipe));
		if (plumb_box == null)
			exit(exit_failure);			//todo must be exit_on_malloc_failure.
	}


