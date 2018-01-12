#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ft_handler_signal(int signo)
{
	printf("JE recois le signal %d\n", signo);
	fflush(stdout);
}

int	main(void)
{
	struct sigaction signal;

	signal.sa_handler = &ft_handler_signal;
	signal.sa_flags = 0;							//FLAG NO POSIX ET PERMET DE NE PAS BLOQUER LES SINAUX
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, 0);
	sigaction(SIGQUIT, &signal, 0);
	sigaction(SIGTERM, &signal, 0);

	while (1);
}
