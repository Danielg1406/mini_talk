/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:49:47 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/11 15:36:59 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

static volatile int	acknowledge_received = 0;

static void	acknowledge_signal(int sig)
{
	(void)sig;
	acknowledge_received = 1;
	write(1, "Message received\n", 18);
}

static void	send_signal(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> (7 - bit)) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				perror("Error sending SIGUSR1");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				perror("Error sending SIGUSR2");
				exit(EXIT_FAILURE);
			}
		}
		usleep(505);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_printf("Usage: ./client <server_pid> <message>\n");
		return (EXIT_FAILURE);
	}
	server_pid = (pid_t)ft_atoi(argv[1]);
	message = argv[2];
	if (signal(SIGUSR1, acknowledge_signal) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (message[i] != '\0')
	{
		send_signal(server_pid, message[i]);
		i++;
	}
	send_signal(server_pid, '\0');
	// while (!acknowledge_received)
	// 	usleep(50);
	return (EXIT_SUCCESS);
}
