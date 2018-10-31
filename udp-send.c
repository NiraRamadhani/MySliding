#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include "frame.h"

int main(int argc, char **argv)
{
	struct sockaddr_in myaddr, remaddr;
	int fd, slen=sizeof(remaddr);
	int recvlen;		/* # bytes in acknowledgement message */
	char *server = "192.168.100.8";	/* change this to use a different server */

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
		// memset(buf_send, 0, sizeof(buf_send));
		// SEND CUSTOM MESSAGE //
		char str[1024];
		printf("SEND MESSAGE : ");
		gets(str);
		// sprintf(buf_send, str);
		// ================== //
		// TEST SEND FRAME //
		buf_send[0] = 0x1; //soh
		int n = 0;
		buf_send[1] = (n >> 24) & 0xFF;
		buf_send[2] = (n >> 16) & 0xFF;
		buf_send[3] = (n >> 8) & 0xFF;
		buf_send[4] = n & 0xFF;
		int data_length = strlen(str);
		buf_send[5] = (data_length >> 24) & 0xFF;
		buf_send[6] = (data_length >> 16) & 0xFF;
		buf_send[7] = (data_length >> 8) & 0xFF;
		buf_send[8] = data_length & 0xFF;
		int cek = (buf_send[5] << 24 ) | (buf_send[6] << 16) | (buf_send[7] << 8) | buf_send[8];
		printf("int: %d\n", cek);
		for(int i = 0; i < data_length; i++){
			buf_send[9+i] = str[i];
		}
		for(int i = 0; i < data_length; i++){
			printf("%c", buf_send[9+i]);
		}
		printf("\n");
		char checksum = 0;
		for(int i = 0; i < 9+data_length; i++){
			checksum += buf_send[i];
		}
		checksum = ~checksum;
		buf_send[9+data_length] = checksum;
		// SEND THE BUFFER //
		if(sendto(fd, buf_send, 1034, 0, (struct sockaddr *)&remaddr, slen)==-1){
			perror("sendto");
			exit(1);
		}
		/* now receive an acknowledgement from the server */
		char* buf_recv=(char*)malloc(6);
		recvlen = recvfrom(fd, buf_recv, 6, 0, (struct sockaddr *)&remaddr, &slen);
		if (recvlen >= 0) {
			buf_recv[recvlen] = 0;	/* expect a printable string - terminate it */
			printf("received message: \"%s\" (%d bytes)\n", buf_recv, recvlen);
		}
	}
	close(fd);
	return 0;
}
