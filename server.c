/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:49:38 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/11 16:03:07 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	character = 0;
	static int	bit_count = 0;

	(void)context;
	if (sig == SIGUSR1)
		character |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		if (character == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
			write(1, &character, 1);
		character = 0;
		bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		write(2, "Error sending acknowledgment\n", 29);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	ft_printf("\033[1;96m");
	ft_printf("\n");
	ft_printf("███╗   ███╗██╗███╗   ██╗██ ████████╗ █████╗ ██╗     ██╗  ██╗\n");
	ft_printf("████╗ ████║██║████╗  ██║██║╚══██╔══╝██╔══██╗██║     ██║ ██╔╝\n");
	ft_printf("██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝ \n");
	ft_printf("██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗ \n");
	ft_printf("██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗\n");
	ft_printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n");
	ft_printf("\nServer PID: %d\n", getpid());
	ft_printf("\033[0m\n");
	set_signal(SIGUSR1, signal_handler, SA_SIGINFO);
	set_signal(SIGUSR2, signal_handler, SA_SIGINFO);
	while (1)
		pause();
	return (0);
}
