#include "command.h"

bool	is_path(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

void	print_error_and_set_es(char *cmd, int exits, char *err)
{
	ft_put_cmd_error(cmd, err);
	g_exit_status = exits;
	return ;
}

bool	check_redirect_file(t_cmd *c, t_exec_attr *ea)
{
	if (has_redirect_file(c))
	{
		if (!open_files(c, ea))
		{
			free(ea->is_unpermitted);
			return (true);
		}
	}
	return (false);
}
