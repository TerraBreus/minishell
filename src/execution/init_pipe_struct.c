//This function is going to create a pipe structure for us.
//It returns -1 if malloc allocation has failed.

int	init_pipe(t_pipe **plumb_box)
{
	if (*plumb_box == NULL)
	{
		plumb_box = (t_pipe *)malloc(sizeof(t_pipe));
		if (plumb_box == NULL)
			return (-1);			//todo must be exit_on_malloc_failure.
	}
	*plumb_box->last_read_end = -1;
	return (0);
}




