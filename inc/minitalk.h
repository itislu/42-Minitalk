/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 23:16:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# include <signal.h>
# include <sys/types.h>

# ifndef MAX_PID
#  define MAX_PID 4194304
# endif
# define SUCCESS 0
# define ARG_ERROR 1
# define HANDSHAKE_ERROR 2
# define SIGEMPTYSET_ERROR 3
# define SIGACTION_ERROR 4
# define KILL_ERROR 5
# define USLEEP_ERROR 6
# define PAUSE_ERROR 7

#endif
