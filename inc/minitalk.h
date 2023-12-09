/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 04:29:47 by ldulling         ###   ########.fr       */
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
#  define MAX_PID				4194304
# endif

/* COMMUNICATION STAGES */
# define HANDSHAKE_STAGE		0
# define LEN_TRANSMISSION_STAGE	1
# define MSG_TRANSMISSION_STAGE	2
# define DISPLAY_MSG_STAGE		3

/* SIGNALS */
# define SIG_HANDSHAKE			SIGUSR1
# define SIG_HANDSHAKE_ERROR	SIGUSR2
# define SIG_SERVER_READY		SIGUSR1
# define SIG_MSG_RECEIVED		SIGUSR2
# ifndef SIG_UINT
#  define SIG_UINT				SIGUSR1
# endif
# ifndef SIG_SIZE_T
#  define SIG_SIZE_T			SIGUSR2
# endif
# ifndef SIG_ONE
#  define SIG_ONE				SIGUSR1
# endif
# ifndef SIG_ZERO
#  define SIG_ZERO				SIGUSR2
# endif

/* EXIT CODES */
# define SUCCESS				0
# define ARG_ERROR				1
# define HANDSHAKE_ERROR		2
# define SIGEMPTYSET_ERROR		3
# define SIGACTION_ERROR		4
# define KILL_ERROR				5
# define USLEEP_ERROR			6
# define PAUSE_ERROR			7
# define MALLOC_ERROR			8
# define TIMEOUT_ERROR			9

#endif
