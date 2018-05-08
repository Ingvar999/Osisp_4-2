#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define LOOPS 2

int number = 1, count = 0;
int children[4] = {0};
int root;
int forexit = 0;
int last;

void handler1(int sig)
{
	printf("Process %d / %d got signal SIGUSR1 from process %d %d\n", number, getpid(), number==1 ? last : getppid(), clock());
	sleep(0.1);
	switch (number)
	{
	case 8:
		kill(root, SIGUSR1);
		printf("Process %d / %d sent signal SIGUSR1 to process %d %d\n", number, getpid(), root, clock());
		break;
	case 1:
	if (forexit++ < LOOPS)
			for (int i = 0; i<4; ++i)
			{
				kill(children[i], SIGUSR2);
				printf("Process %d / %d sent signal SIGUSR2 to process %d %d\n", number, getpid(), children[i], clock()); 
			}
	else 
		{
			int stat;
			for (int i= 0; i<4; ++i)
			wait(&stat);
		}
	break;
	}	
}

void handler2(int sig)
{
	printf("Process %d / %d got signal SIGUSR2 from process %d %d\n", number, getpid(), getppid(), clock());
	switch (number)
	{
	case 5:
		break;
	case 2:case 3:case 4:
		kill(children[0], SIGUSR1);
		printf("Process %d / %d sent signal SIGUSR1 to process %d %d\n", number, getpid(), children[0], clock());
		break;
	} 
}

int main(int argc, char* argv[])
{
	int temp = 0;
	root = getpid();
	while (number == 1 && count < 4)
	{
		if (temp = fork())
			children[count++] = temp;
		else
		{
			
			number += count + 1;
			count = 0;
		}
	}
	switch (number)
	{
		case 2:
		if (temp = fork())
			children[0] = temp;
		else
			number = 6;
		break;
		case 3:
		if (temp = fork())
			children[0] = temp;
		else
			number = 7;
		break;
		case 4:
		if (temp = fork())
			children[0] = temp;
		else
		{
			last = getpid();
			number = 8;
		}
		break;
	}
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = handler1;
	sigaction(SIGUSR1, &act, 0);
	act.sa_handler = handler2;
	sigaction(SIGUSR2, &act, 0);
	if (number == 1)
	{
		system("ps fax");
		kill(root, SIGUSR1);
	}
	int i = 0;
	while (i++ <= LOOPS)
		sleep(1);
	return 0;
}
