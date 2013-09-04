
#include <string.h>       /* for bzero() */
#include <stdio.h>        /* for stdout, EOF */
#include <unistd.h>       /* for read() */
#include <stdlib.h>       /* for exit() */
#include <sys/socket.h>   /* for socket ops */
#include <netinet/in.h>   /* for sockaddr_in struct */
#include <arpa/inet.h>    /* for inet_pton() */

#define MAXLINE 	4096
#define SA 		struct sockaddr

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	printf(" day time tcp client start !\n");
	if (argc != 2)
		printf("usage: a.out <IPaddress>\n");

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket error\n");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13); /* from daytime server port */

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s\n", argv[1]);

	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		printf("connect error\n");

	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
			printf("fputs error\n");
	}

	if (n < 0)
		printf("read error\n");

	exit(0);
}
