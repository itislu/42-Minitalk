/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 23:17:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

/* Server */
void	handle_signal(int signo, siginfo_t *info, void *context);
bool	display_msg(int signo, siginfo_t *info);

/* Handshake */
void	handshake(siginfo_t *info);

#endif
