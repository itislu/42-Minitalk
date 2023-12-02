/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:06:11 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 01:50:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	check_input(int argc, char *argv[])
{
	if (argc < 2)
		ft_printf("Enter a server PID.\n");
	else if (argc > 3)
		ft_printf("Invalid number of arguments.\n");
	else
	{
		if (is_valid_pid(argv[1]))
		{
			if (kill(ft_atoi(argv[1]), 0) != -1)
				return (1);
			else if (argc == 3 && is_valid_pid(argv[2]))
				return (2);
			else
				return (1);
		}
		else if (argc == 3 && is_valid_pid(argv[2]))
			return (2);
		else
			ft_printf("One argument has to be a valid PID.");
	}
	return (-1);
}

bool	is_valid_pid(char *arg)
{
	if (ft_strisdigits(arg) && (unsigned int) ft_atoi(arg) <= MAX_PID)
		return (true);
	else
		return (false);
}
