#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(const char * program, char ** arg_list) { 
	pid_t child_pid = fork();
	if (child_pid != 0)
		return child_pid;      /* This is the parent process.  */
	else {
		execvp (program, arg_list);     /* Now execute PROGRAM */
		fprintf (stderr, "An error occurred in execvp\n");
		abort();
	}
}

int main() { 
	char * arg_list[] = { "ls", "-l", "/", NULL };
	spawn("ls", arg_list); 
	printf ("Main program exiting...\n");
	return 0; 
}
