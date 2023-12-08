/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 02:11:28 by ldulling         ###   ########.fr       */
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

/* SIGNALS */
# define SIG_HANDSHAKE SIGUSR1
# define SIG_HANDSHAKE_ERROR SIGUSR2
# define SIG_SERVER_READY SIGUSR1
# define SIG_SERVER_ERROR SIGUSR2
# ifndef SIG_INT
#  define SIG_INT SIGUSR1
# endif
# ifndef SIG_LONG
#  define SIG_LONG SIGUSR2
# endif
# ifndef SIG_ONE
#  define SIG_ONE SIGUSR1
# endif
# ifndef SIG_ZERO
#  define SIG_ZERO SIGUSR2
# endif

/* EXIT CODES */
# define SUCCESS 0
# define ARG_ERROR 1
# define HANDSHAKE_ERROR 2
# define SIGEMPTYSET_ERROR 3
# define SIGACTION_ERROR 4
# define KILL_ERROR 5
# define USLEEP_ERROR 6
# define PAUSE_ERROR 7
# define MALLOC_ERROR 8
# define SERVER_ERROR 9

#endif
