/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:06:11 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/29 00:10:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	check_input(int argc, char *argv[])
{
	if (argc < 2)
		ft_printf("Enter a PID.\n");
	else if (argc > 3)
		ft_printf("Invalid number of arguments.\n");
	else
	{
		if (ft_strisdigits(argv[1]))
			return (1);
		else if (argc == 3 && ft_strisdigits(argv[2]))
			return (2);
		else
			ft_printf("One argument has to be a PID.");
	}
	return (-1);
}
