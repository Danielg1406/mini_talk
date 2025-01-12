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

volatile sig_atomic_t	g_acknowledge_received = 0;

static void	received_message(int sig)
{
	(void)sig;
	write(1, "\n\tMessage received by server\n", 29);
	exit(EXIT_SUCCESS);
}

static void	acknowledge_signal(int sig)
{
	(void)sig;
	g_acknowledge_received = 1;
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
				write(2, "Error sending SIGUSR1", 22);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				write(2, "Error sending SIGUSR2", 22);
				exit(EXIT_FAILURE);
			}
		}
		bit++;
		while (!g_acknowledge_received)
			usleep(50);
		g_acknowledge_received = 0;
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
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	set_signal(SIGUSR1, acknowledge_signal, 0);
	set_signal(SIGUSR2, received_message, 0);
	i = 0;
	while (message[i] != '\0')
	{
		send_signal(server_pid, message[i]);
		i++;
	}
	send_signal(server_pid, '\0');
	return (EXIT_SUCCESS);
}
