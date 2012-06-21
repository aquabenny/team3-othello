
/** Simple Iterating Telnet Server - Does not implement: http://datatracker.ietf.org/doc/rfc854/ **/
/*	Demonstrates use of system calls socket(), bind(),
 *	listen(), accept(), read(), write() on the server side
 * 	The client is expected to be telnet. Single client. 
 *	This makes no consideration for security. This is a simple example to get started
 */

/* To compile: gcc -o telnetServerDemo telnetServerDemo.c -lnsl -lsocket -lresolv
* on Solaris the basic socket functions are in different libraries and we add -lsocket -lnsl to link 
* against the libsocket and libnsl dynamic libraries. In this particular example, -lnsl & -lresolv 
* are unused. For most linux and mac's, the necessary symbols are in libc, so none of the 
* linking is necessary
*  To start server: ./telnetServerDemo 65135
*/

/* To run this: From any machine (including sun) - $telnet sun.cs.tamu.edu 65135. From the telnet 
 * prompt type any of: alpha beta gamma delta epsilon and the server should ack back. To exit, type
 * Ctrl+]quit or simply type exit. When using Putty for Telnet, use Passive Mode.
 * More about Telnet options in Putty here: http://www.yz.kiev.ua/www/etc/putty/Section3.12.html
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/shm.h>
#include<time.h>
#include <vector>
#include <iostream>
#include<strings.h>
using namespace std;

#define SERV_PORT  65144	/* Default */

int main(int argc, char *argv[]) {   

	int server_socket_fd;       /* file descriptor into transport */
    int client_socket_fd;           /* file descriptor to accept on   */
    socklen_t client_addr_length;          /* length of address structure    */
    struct sockaddr_in server_addr; /* address of server   */
    struct sockaddr_in client_addr; /* address of client   */
    int server_port;
    if (argc != 2) 					/* If no port is specified, default */
    	server_port = SERV_PORT;	
    else
    	server_port = atoi(argv[1]);
    
    /* Create a Stream socket (TCP/IP). Uses Internet Domain. 0 lets OS choose appropriate protocol 
     * which will most likely be TCP for SOCK_STREAM and UDP for SOCK_DGRAM. Also checks for error*/
    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(1);
    }
    
    /* Set up (Fill in) server address i.e. sockaddr_in server_addr */
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /*Allows multiple interfaces */
    server_addr.sin_port = htons(server_port); /* Convert to network byte order */
    
    /* Optional: Enables reuse of a socket in TIME_WAIT state. See last line of main for why? */
    int optval=1;
    setsockopt(server_socket_fd,SOL_SOCKET,SO_REUSEADDR, &optval, sizeof optval);
    
    /* Bind IP Address/port number to socket. Check for errors */
    /* bind(socket file descriptor, address to be bound to, size of address to which it is bound) */
    /* second argument is of type sockaddr but what is passed in is of type sockaddr_in. Typecast */
    if (bind(server_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(1);
    }
    
    /* 	Set the socket up for listening, with a queue length of 1. Queue Length indicates the number 
     *	of pending connections it will hold. The max on most systems is 5. This is unlikely to fail*/
	if (listen(server_socket_fd, 1) < 0) {
        perror("listen failed");
        exit(1);
    }
    
	
	 /* Accept a Client Connection. accept() is blocking. Returns a file descriptor for client. 
	 * 	Second argument is reference pointer to address of client on other end. 
	 * 	Second argument is of type sockaddr but what is passed in is of type sockaddr_in.Typecast*/
    client_addr_length = sizeof(client_addr);
    printf("Waiting for connection....\n");
    if ((client_socket_fd = accept(server_socket_fd,(struct sockaddr *)&client_addr, &client_addr_length)) < 0) {
        	perror("could not accept call");
            exit(1);
    }
    
    /* OPTIONAL - Welcome Message */
    char welcome_msg[BUFSIZ];
    sprintf(welcome_msg,"Welcome to Single Client Telnet Server Demo\n\r");
    if (write(client_socket_fd, &welcome_msg, strlen(welcome_msg)) < 0) {
    		perror("write failed!");
	        exit(1);
    }
    
    /* Buffer, Reply and Control Variables */
    int done = 0;    			/* indicates all data is read        */
    int where = 0;   			/* points to where we are in buffer  */
	int nbytes = 0;      			/* the number of bytes read          */
    char reply[BUFSIZ];      	/* a buffer to send replies to client */
	char buf[BUFSIZ];			/* buffer to hold incoming command    */
	
    /*	Loop continuously, respond to single client's requests*/
    while (1) {
    	printf("Waiting to receive data....\n");
    	bzero(buf,BUFSIZ);
    	done = 0;
    	where =0;
    	
        /* Read data from client. Read will block until there is something to read */
        /* Note that read operates on the new file descriptor from accept */
        /* It will read total number of characters in socket or BUFSIZ, whichever is less */
    	do {
	    	if ((nbytes = read(client_socket_fd, &buf[where],BUFSIZ)) < 0) {
        		perror("read of data failed!");
				exit(1);
        	}
    		where += nbytes;
    		if (buf[where-1] == '\n') {
    			buf[where-1]='\0';
        		done = 1;
	        	printf ("Received Data\n");
    	    }
	    } while (!done);
	    
	   printf("Received nbytes=%d, Received buf=%s\n",nbytes, buf);
	   printf("strlen(buf)=%d\n",strlen(buf));
	   
	   if (strncmp(buf,"alpha",5)==0){
	    	strcpy(reply,"server acks alpha\n\r");
	    } else if (strncmp(buf,"beta",4)==0) {
    		strcpy(reply,"server acks beta\n\r");
    	} else if (strncmp(buf,"gamma",5)==0) {
    		strcpy(reply,"server acks gamma\n\r");
    	} else if (strncmp(buf,"delta",5)==0) {
    		strcpy(reply,"server acks delta\n\r");
    	} else if (strncmp(buf,"epsilon",7)==0) {
    		strcpy(reply,"server acks epsilon\n\r");
    	} else if (strncmp(buf,"CREATE",6)==0) {
			send(client_socket_fd,"You said CREATE!!!\n",strlen("You said CREATE!!!\n"),0);
		} else if (strncmp(buf,"exit",4)==0) {
	   		break;
    	} else {
    		strcpy(reply,"received illegal\n\r");
    	}
    
	    printf("Reply sent to client=%s",reply);   
	   
	   /*
     	*  Send reply to client.
     	*/
    	if (write(client_socket_fd, &reply, strlen(reply)) < 0) {
    		perror("write failed!");
	        exit(1);
    	}
    }//End While(1)

if (shutdown(client_socket_fd,SHUT_RDWR)<0) {
	perror("shutdown failure");
	exit(1);
}

close(client_socket_fd);
/*Possible to properly close a TCP Connection?: Read http://hea-www.harvard.edu/~fine/Tech/addrinuse.html */

return 0;
}



/*
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/shm.h>
#include<time.h>
#include <vector>
#include <iostream>
#include<strings.h>
using namespace std;

#define PERM S_IRUSR|S_IWUSR
#define BACKLOG 10 
#define MYPORT 22

int main(){
	int clientfd,recvbytes;
	socklen_t sin_size;
	char *buf, *r_addr, *w_addr, *temp, *time_str;
	struct sockaddr_in their_addr;

	//create socket
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	//bind
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero),0);

	if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}
	
	while(1){
		//listen
		if(listen(sockfd,BACKLOG) == -1){
			perror("listen");
			exit(1);
		}
		
		//accept
		if((clientfd = accept(sockfd,(struct sockaddr*)&their_addr,&sin_size)) == -1){
			perror("accept");
			exit(1);
		}
		
		//get message
		buf = (char *)malloc(255);
		memset(buf,0,255);
		if((recvbytes = recv(clientfd,buf,255,0)) <= 0){
			perror("recv1");
			close(clientfd);
			raise(SIGKILL);
			exit(1);
		}
		
		//handle request
		if(strcmp(buf,"CREATE")==0){
			send(clientfd,"You said CREATE!!!\n",strlen("You said CREATE!!!\n"),0);
			if((recvbytes = recv(clientfd,buf,255,0)) <= 0){
				perror("recv1");
				close(clientfd);
				raise(SIGKILL);
				exit(1);
			}
		}
		else if(buf == "JOIN"){
			send(clientfd,"Please Enter a chatroom name\n",strlen("Please Enter a chatroom name\n"),0);
			if((recvbytes = recv(clientfd,buf,255,0)) <= 0){
				perror("recv1");
				close(clientfd);
				raise(SIGKILL);
				exit(1);
			}
		}
		else if(buf == "DELETE"){
			send(clientfd,"Please Enter a chatroom name\n",strlen("Please Enter a chatroom name\n"),0);
			if((recvbytes = recv(clientfd,buf,255,0)) <= 0){
				perror("recv1");
				close(clientfd);
				raise(SIGKILL);
				exit(1);
			}
		}
		else{
			send(clientfd,"Invalid command\n",strlen("Invalid command\n"),0);
		}
		
		//close connection
		close(clientfd);	
	}//end of while
}
*/
