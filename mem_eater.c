#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>


void request_bytes();
void display_stats();


const static int numBytes = 0x7fffffff;
static long long numBlocks = 0;
long long bytesRequested = 0;

int main() {
	/* Registers the signal handler for ^C. */
	signal(SIGINT, display_stats);
	request_bytes();
	return 0;
}

void request_bytes() {
	void* pointer;
	while(1){
		pointer = malloc(numBytes);
		if(pointer) {
			*(short *)(pointer + 0xface) = 0xbead;
			numBlocks++;
			printf("Memory requested.\n");
		}
		if(errno == ENOMEM) {
			/* If no more memory is available to be leaked,
			 * 	the program ^C's itself so that statistics
			 * 	can be displayed.
			 */
			kill(getpid(), SIGINT);
		}
	}
}

void display_stats() {
	long long gbLeaked;
	long long tbLeaked;

	bytesRequested = numBytes * numBlocks;
	
	/* Calculates the numbers of GBs and TBs leaked. 
	 * I always round up. */
	gbLeaked = 1 + (bytesRequested >> 30);
	tbLeaked = 1 + (bytesRequested >> 40);
	
	/*	Each printf is very expensive because of the number of system
			calls they entail.
		However, one call is used per line because that 
			is easier for the programmer to read.
	*/
	printf("\nBlock Size : %d bytes.\n", numBytes);
	printf("Blocks requested : %d.\n\n", numBlocks);

	printf("Total bytes leaked : %lld bytes.\n", bytesRequested);
	printf("Total bytes leaked : %lld GB.\n", gbLeaked);
	printf("Total bytes leaked : %lld TB.\n", tbLeaked);

	exit(0);
}
