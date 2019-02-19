#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	pid_t child_pid;
	printf("Main process id = %d (parent PID = %d)\n", (int) getpid(), (int)  getppid());
	child_pid = fork();
	if (child_pid != 0)
		printf("Parent: child's process id = %d\n", child_pid);
	else
		printf("Child:  my process id = %d\n", (int) getpid()); 
	return 0;
}
