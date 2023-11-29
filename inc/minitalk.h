/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/29 16:10:53 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include "ft_printf.h"
# include <signal.h>
# include <sys/types.h>

# ifndef MAX_PID
#  define MAX_PID 4194304
# endif

/* Structs */
typedef struct s_stacks
{
	t_list_d	*top_a;
	t_list_d	*top_b;
	t_list_d	*bottom_a;
	t_list_d	*bottom_b;
}	t_stacks;

/* Functions */


#endif