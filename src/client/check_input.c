/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:06:11 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/01 19:08:23 by ldulling         ###   ########.fr       */
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
		if (ft_strisdigits(argv[1]))
		{
			if (kill(ft_atoi(argv[1]), 0) != -1)
				return (1);
			else if (argc == 3 && ft_strisdigits(argv[2]))
				if ((unsigned int) ft_atoi(argv[2]) <= MAX_PID)
					return (2);
		}
		else if (argc == 3 && ft_strisdigits(argv[2]))
			if ((unsigned int) ft_atoi(argv[2]) <= MAX_PID)
				return (2);
		ft_printf("One argument has to be a valid PID.");
	}
	return (-1);
}
