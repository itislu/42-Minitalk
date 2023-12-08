/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_display_msg_stage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:48:10 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/07 11:48:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	display_msg(char **msg)
{
	ft_printf("%s", *msg);
	free_and_null(msg);	//Maybe (void **) necessary
	// free(*msg);
	// *msg = NULL;
}
