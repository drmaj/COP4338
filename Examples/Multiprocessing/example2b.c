#include <sys/wait.h> 
#include <unistd.h> 
#include <stdio.h>

void one_at_a_time( const char * str ) { 
	while( *str!= '\0' ) { 
		putchar( *str++ );   // Write a char and increment the pointer
		fflush( stdout );    // Print out immediately (no buffering)
		sleep(1);
	} 
} 

void main() { 
	if( fork() == 0 ) 
		one_at_a_time( "............." ); 
	else {
		wait( NULL );
		one_at_a_time( "|||||||||||||" ); 
	}
	printf("\n");
}
