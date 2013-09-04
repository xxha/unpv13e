#include <time.h>

#define MAXLINE 	4096

int main(int argc, char **argv)
{
	int 			listenfd, connfd;
	struct sockaddr_in 	servaddr;
	char 			buff[MAXLINE]
	time_t 			ticks;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket error\n");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family 	= AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port 	= htons(13);

	if ((bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
		printf("bind error\n");

	if (listen(listenfd, LISTENQ) < 0)
		printf("listen error\n");

	for ( ; ; ) {
		if ((connfd = Accept(listenfd, (SA *)NULL, NULL)) < 0)
			printf("accept error\n");
		ticks = time(NULL);

		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if (write(connfd, buff, strlen(buff)) != strlen(buff))
			printf("write error\n");

		if(close(connfd) != -1)
			printf("close error\n");;
	}
}
