/*
	demo-udp-03: udp-send: a simple udp client
	send udp messages
	This sends a sequence of messages (the # of messages is defined in MSGS)
	The messages are sent to a port defined in SERVICE_PORT 

	usage:  udp-send

	Paul Krzyzanowski
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include "frame.h"

#define BUFLEN 2048
#define MSGS 5	/* number of messages to send */

int main(void)
{
	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen=sizeof(remaddr);
	char buf[BUFLEN];	/* message buffer */
	int recvlen;		/* # bytes in acknowledgement message */
	char *server = "10.18.103.9";	/* change this to use a different server */
	// char str[100];

	/* create a socket */

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}       

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	//INIT READ FILE
	// FILE *fp;
	// fp = fopen("./data/data.txt", "r");
	// // if(fp == NULL){
	// // 	die("Couldn't open file");
	// // }
	// int Max_Frame = 10; //dari inputan
	// frame frm[Max_Frame];
	// int frameNum = 0;
	// //BUAT FRAME DARI READ
	// while(fgets(buf, 1024, (FILE*)fp)){
	// 	frm[frameNum] = create_frame(frameNum, buf);
	// 	frameNum++;
	// }
	/* now let's send the messages */
	for(int i = 0; i < 1; i++){
		// printf("ini: %d\n", strlen(buf));
		printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
		char* buf_send=(char*)malloc(1034);
		// frame_to_raw(frm[i], buf_send);
		memset(buf_send, 0, sizeof(buf_send));
		sprintf(buf_send, "TEST SEND INI");
		// printf("ini: %d\n", sizeof(buf_send));
		printf("cek: %x", buf_send[0]);
		if(sendto(fd, buf_send, 1034, 0, (struct sockaddr *)&remaddr, slen)==-1){
			perror("sendto");
			exit(1);
		}
		/* now receive an acknowledgement from the server */
		recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &slen);
		if (recvlen >= 0) {
			buf[recvlen] = 0;	/* expect a printable string - terminate it */
			printf("received message: \"%s\"\n", buf);
		}
	}

	// for (i=0; i < MSGS; i++) {
	// 	printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
	// 	gets(str);
	// 	sprintf(buf, str);
	// 	printf("%s\n", buf);
	// 	if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1) {
	// 		perror("sendto");
	// 		exit(1);
	// 	}
	// 	/* now receive an acknowledgement from the server */
	// 	recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &slen);
	// 	if (recvlen >= 0) {
	// 		buf[recvlen] = 0;	/* expect a printable string - terminate it */
	// 		printf("received message: \"%s\"\n", buf);
	// 	}
	// }
	close(fd);
	return 0;
}
