#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int ac, char **av, char **env)
{
	ac = (int)ac;
	int child;

		execve("/bin/ls", av, env);
	printf("test");
}

