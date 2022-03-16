
#include "command.h"

int	execute_cmd(t_exec_attr *ea)
{
	int	pipe_count;

	if (ea->cmd_lst == NULL)
		return (0);
	pipe_count = ft_lstsize(ea->cmd_lst) - 1;
	if (pipe_count == 0)
	{
		no_pipe_process(ea);
	}
	else
	{
		pipe_process(ea, pipe_count);
	}
	return (0);
}
