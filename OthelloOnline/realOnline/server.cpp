
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

#include "ai.h"

#define SERV_PORT  65144	/* Default */

int main(int argc, char *argv[]) {   

	/****************************************************SET UP CONNECTION***************************************************/

	Othello o;
	AI ai1, ai2;
	string input;
	int rc = 0;

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
    sprintf(welcome_msg,"Welcome to the best Othello game eva!\n\r");
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
	
	/*********************************************************SET UP AI*****************************************************/
	
	//set difficulty
	bool goAgain = false;
	char prompt[BUFSIZ];
	do{
		sprintf(prompt,"\nEnter a difficulty\n\r>");
		if (write(client_socket_fd, &prompt, strlen(prompt)) < 0) {
    		perror("write failed!");
	        exit(1);
		}
		bzero(buf,BUFSIZ);
		done = 0;
		where =0;
		
		//read
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
		
		if (strncmp(buf,"EASY",4)==0) {
	    	strcpy(reply,"EASY does it\n\r");
			ai1.setDifficulty(EASY);
			goAgain = false;
	    } else if (strncmp(buf,"MEDIUM",6)==0) {
    		strcpy(reply,"GREEDY!!!\n\r");
			ai1.setDifficulty(MEDIUM);
			goAgain = false;
    	} else if (strncmp(buf,"HARD",4)==0) {
    		strcpy(reply,"You gonna lose!\n\r");
			ai1.setDifficulty(HARD);
			goAgain = false;
    	} else {
			strcpy(reply,"Invalid difficulty\n\r");
			goAgain = true;
		}
		if (write(client_socket_fd, &reply, strlen(reply)) < 0) {
    		perror("write failed!");
	        exit(1);
    	}
	}while(goAgain);
	
	//set color
	goAgain = false;
	do{
		sprintf(prompt,"\nEnter a color\n\r>");
		if (write(client_socket_fd, &prompt, strlen(prompt)) < 0) {
    		perror("write failed!");
	        exit(1);
		}
		bzero(buf,BUFSIZ);
		done = 0;
		where =0;
		
		//read
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
		
		if (strncmp(buf,"BLACK",5)==0) {
	    	strcpy(reply,"You go first!\n\r");
			ai1.setPlayerColor(WHITE);
			goAgain = false;
	    } else if (strncmp(buf,"WHITE",5)==0) {
    		strcpy(reply,"Wait your turn!\n\r");
			ai1.setPlayerColor(BLACK);
			goAgain = false;
    	} else {
			strcpy(reply,"Invalid color\n\r");
			goAgain = true;
		}
		if (write(client_socket_fd, &reply, strlen(reply)) < 0) {
    		perror("write failed!");
	        exit(1);
    	}
	}while(goAgain);
	
	{
		string str = o.print(BLACK);
		char board [4096];
		sprintf(board, str.c_str());
		if (write(client_socket_fd, &board, strlen(board)) < 0) {
			perror("write failed!");
			exit(1);
		}
	}
	
    /*********************************************************PLAY GAME*****************************************************/
		
		ParseReturn pr;
		pr.str = "";
		pr.val = 0;
    while (pr.val != 2) {
		//blacks turn
		do{
			if(ai1.getColor() == BLACK){		//ai is black
				sprintf(prompt,"\nBLACK>");
				if (write(client_socket_fd, &prompt, strlen(prompt)) < 0) {
					perror("write failed!");
					exit(1);
				}
					pr = o.parse(ai1.go(o), BLACK);
					char board [4096];
					sprintf(board, pr.str.c_str());
				if (write(client_socket_fd, &board, strlen(board)) < 0) {
					perror("write failed!");
					exit(1);
				}
			}
			else{		//human is black
				sprintf(prompt,"\nBLACK>");
				if (write(client_socket_fd, &prompt, strlen(prompt)) < 0) {
					perror("write failed!");
					exit(1);
				}
				
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
				
				input = buf;
				input.erase(input.end()-1);
				pr = o.parse(input, BLACK);
				char board [4096];
				sprintf(board, pr.str.c_str());
				if (write(client_socket_fd, &board, strlen(board)) < 0) {
					perror("write failed!");
					exit(1);
				}
			}
		}while(pr.val == 0);
		if(pr.val != 2) {
			//whites turn
			do{
				if(ai1.getColor() == WHITE){		//ai is white
					sprintf(prompt,"\nWHITE>");
					if (write(client_socket_fd, &prompt, strlen(prompt)) < 0) {
						perror("write failed!");
						exit(1);
					}
					pr = o.parse(ai1.go(o), WHITE);
					char board [4096];
					sprintf(board, pr.str.c_str());
					if (write(client_socket_fd, &board, strlen(board)) < 0) {
						perror("write failed!");
						exit(1);
					}
				}
				else{		//human is white
					sprintf(prompt,"\nWHITE>");
					if (write(client_socket_fd, &prompt, strlen(prompt)) < 0) {
						perror("write failed!");
						exit(1);
					}
					
					bzero(buf,BUFSIZ);
					done = 0;
					where = 0;
					
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
					
					input = buf;
					input.erase(input.end()-1);
					pr = o.parse(input, WHITE);
					char board [4096];
					sprintf(board, pr.str.c_str());
					if (write(client_socket_fd, &board, strlen(board)) < 0) {
						perror("write failed!");
						exit(1);
					}
				}
			}while(pr.val == 0);
		}
    }//End While(pr.val != 2)

	if (shutdown(client_socket_fd,SHUT_RDWR)<0) {
		perror("shutdown failure");
		exit(1);
	}

	close(client_socket_fd);
	/*Possible to properly close a TCP Connection?: Read http://hea-www.harvard.edu/~fine/Tech/addrinuse.html */

	return 0;
}
