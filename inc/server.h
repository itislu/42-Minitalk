/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 02:47:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define HANDSHAKE_STAGE 0
# define GET_LEN_STAGE 1
# define BUFFER_MSG_STAGE 2
# define DISPLAY_MSG_STAGE 3

extern volatile char	*g_msg[];

/* Server */
void	handle_signal(int signo, siginfo_t *info, void *context)

/* Server utils */
void	free_all_and_exit(int exit_code);
void	set_bit(void *byte, int signo);

/* 01 Handshake stage */
void	handshake(siginfo_t *info, int stage[]);

/* 02 Get len stage */
int		get_len(size_t *len, int signo, pid_t pid);
int		get_lentype(int signo);

/* 03 Buffer msg stage */
int		buffer_msg(size_t *len, int signo, pid_t pid);

/* 04 Display msg stage */
void	display_msg(char **msg);

#endif
