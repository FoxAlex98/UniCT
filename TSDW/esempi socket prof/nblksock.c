/* nblksock.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{	
	int s;
	unsigned int flags;

	s = socket(PF_UNIX,SOCK_DGRAM,0);

// Code below could be shortened, but is clearer thus
	
	printf("Current flags:   %.8x |\n", flags = fcntl(s,F_GETFL));
	printf("O_NONBLOCK =     %.8x =\n", O_NONBLOCK);	
	flags |= O_NONBLOCK;
	printf("                 %.8x\n", flags);
	printf("Setting flags to %.8x\n", flags);
	fcntl(s,F_SETFL,flags);
	printf("Current flags:   %.8x\n\n", fcntl(s,F_GETFL));

	printf("Current flags:   %.8x &\n", flags = fcntl(s,F_GETFL));
	printf("~O_NONBLOCK =    %.8x =\n", ~O_NONBLOCK);	
	flags &= ~O_NONBLOCK;
	printf("                 %.8x\n", flags);
	printf("Setting flags to %.8x\n", flags);
	fcntl(s,F_SETFL,flags);
	printf("Current flags:   %.8x\n\n", fcntl(s,F_GETFL));

	printf("Current flags:   %.8x\n", flags = fcntl(s,F_GETFL));
	printf("Setting flags to %.8x\n", 0x0);
	fcntl(s,F_SETFL,0x0);
	printf("Current flags:   %.8x\n", flags = fcntl(s,F_GETFL));
	printf("NB: fnctl() cannot change "); 
	printf("access mode bits (LSB and LSB+1)\n");
	// vedi: http://www.gnu.org/software/libc/manual/html_mono/libc.html#File-Status-Flags

	close(s);
	exit(0);
}
