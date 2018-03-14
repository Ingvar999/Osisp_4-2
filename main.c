#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int number = 1, count = 0;
int children[4] = {0};

void handler1(int sig)
{
	printf("%d\n", sig); 
}

void handler2(int sig)
{
	
}

int main(int argc, char* argv[])
{
	signal(SIGUSR1, handler1);
	signal(SIGUSR2, handler2);
	int temp = 0;
	while (number == 1 && count < 4)
	{
		if (temp = fork())
			children[count++] = temp;
		else
			number += count + 1;
	}
	count = 0;
	switch (number)
	{
		case 2:
		if (temp = fork())
			children[count++] = temp;
		else
			number = 6;
		break;
		case 3:
		if (temp = fork())
			children[count++] = temp;
		else
			number = 7;
		break;
		case 4:
		if (temp = fork())
			children[count++] = temp;
		else
			number = 8;
		break;
	}
	sleep(0.1);
	//printf("%d\n", number);
	if (number != 1)
	kill(getppid(), SIGUSR1);
	sleep(3);
	return 0;
}
