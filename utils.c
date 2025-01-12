#include "mini_talk.h"

void	set_signal(int sig, void *signal_handler, int flag)
{
	struct sigaction sa;

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