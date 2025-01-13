/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:27:35 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/12 12:28:28 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	received_message(int sig)
{
	(void)sig;
	write(1, "\n\tMessage received by server\n", 29);
	exit(EXIT_SUCCESS);
}

void	error_signal(pid_t pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		write(2, "Error sending signal\n", 21);
		exit(EXIT_FAILURE);
	}
}

void	set_signal(int sig, void *signal_handler, int flag)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (flag == SA_SIGINFO)
	{
		sa.sa_flags = flag;
		sa.sa_sigaction = signal_handler;
	}
	else
		sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(sig, &sa, NULL) == -1)
	{
		write(2, "Error setting signal\n", 21);
		exit(EXIT_FAILURE);
	}
}
