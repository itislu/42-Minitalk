/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:06:11 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/10 00:17:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	parse_input(int argc, char *argv[], char **msg, pid_t *pid_server)
{
	int		argno_msg;
	int		argno_pid;

	argno_pid = check_input(argc, argv);
	if (argno_pid == -1)
		exit (ARG_ERROR);
	if (argc == 3)
	{
		argno_msg = argno_pid % 2 + 1;
		*msg = argv[argno_msg];
	}
	else
		*msg = NULL;
	*pid_server = ft_atoi(argv[argno_pid]);
}

int	check_input(int argc, char *argv[])
{
	enum e_dangerous_pid	dangerous_pid;

	dangerous_pid = OK;
	if (argc < 2)
		ft_printf("Enter a server PID.\n");
	else if (argc > 3)
		ft_printf("Invalid number of arguments.\n");
	else
	{
		if (is_valid_pid(argv[1], &dangerous_pid))
		{
			if (kill(ft_atoi(argv[1]), 0) != -1)
				return (1);
			else if (argc == 3 && is_valid_pid(argv[2], &dangerous_pid))
				return (2);
			else
				return (1);
		}
		else if (argc == 3 && is_valid_pid(argv[2], &dangerous_pid))
			return (2);
		else if (dangerous_pid == OK)
			ft_printf("One argument has to be a valid PID.\n");
	}
	check_dangerous_pid(dangerous_pid);
	return (-1);
}

bool	is_valid_pid(char *arg, enum e_dangerous_pid *dangerous_pid)
{
	int	pid;

	if (arg && ft_strlen(arg) < 10)
	{
		if (ft_strisdigits(arg))
		{
			pid = ft_atoi(arg);
			if (pid == 0)
				*dangerous_pid = ZERO;
			else if (pid <= MAX_PID)
				return (true);
		}
		else if (arg[0] == '-')
		{
			if (ft_strcmp(arg, "-1") == 0)
				*dangerous_pid = MINUS_ONE;
			else if (ft_strisdigits(&arg[1]))
				*dangerous_pid = NEGATIVE;
		}
	}
	return (false);
}

void	check_dangerous_pid(enum e_dangerous_pid dangerous_pid)
{
	if (dangerous_pid == OK)
		return ;
	else if (dangerous_pid == ZERO || dangerous_pid == NEGATIVE)
		ft_printf("Please enter one specific server pid.\n");
	else if (dangerous_pid == MINUS_ONE)
		ft_printf("You don't wanna do this, trust me.\n");
}
