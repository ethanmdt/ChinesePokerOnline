#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
#define STDIN 0
#define LENGTH 128
void error(const char *msg) {
	fprintf(stderr, msg);
	exit(1);
}
static void sig_child(int signo) {
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0);
	return;
}
int sendall(int sock, char *buf, int len) {
	int n, total = 0, bytesleft = len;
	while (total < len) {
		n = send(sock, buf+total, bytesleft, 0);
		if (n == -1) { break; }
		total += n;
		bytesleft -= n;
	}
	return n==-1?-1:0;
}
int main(int argc, char *argv[])
{
	if (fork()) exit(0);
	signal(SIGCHLD, sig_child);
	setsid();
	if (fork()) exit(0);
	umask(0);
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 500000;
    fd_set readfds, writfds, master, masterW;
    FD_ZERO(&master);
    FD_ZERO(&masterW);
    char buf[LENGTH], name[LENGTH];
	socklen_t clilen;
    int newfd, sockfd, nbytes, portno, opts, maxfd = 0, yes = 1;
    struct sockaddr_in serv_addr, cli_addr;
    vector<int> listener;
    if (argc < 3) error("no port provided\n");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) error("ERROR opening socket\n");
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) error("ERROR setting socket\n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR binding\n");
    if (listen(sockfd, 5) < 0) error("EROOR listening\n");
    opts = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, opts | O_NONBLOCK);
    if (sockfd > maxfd) maxfd = sockfd;
    FD_SET(sockfd, &master);
    clilen = sizeof cli_addr;
    
	chdir("/home/asy");
	FILE *pFile, *qFile = fopen(argv[2], "r");
	chdir("/");
   int len;
    double sum = 0, pre = 0;
   	unsigned int len0 = 0, namelen = 0;
    bool flag = false, flag1 = true;
    while (true) {
    	readfds = master;
        writfds = masterW;
        if (select(maxfd+1, &readfds, &writfds, NULL, &tv) < 0) error("ERROR selecting\n");
		for (int i = 0; i <= maxfd; i++)
		  if (FD_ISSET(i, &writfds) && i!=sockfd) {
        	 if (flag1) {
				bzero(buf, sizeof buf);
				strcpy(buf+1, argv[2]);
				buf[0] = strlen(argv[2]);
    	   	    sendall(i, buf, buf[0]+1);
				printf("send file name: %s\n", buf+1);
    	        flag1 = false;
       		 } else {
			bzero(buf, sizeof buf);
           		 len = fread(buf+1, sizeof(char), (sizeof buf)-1, qFile);
           		 buf[0] = len;
				if (len+1 < LENGTH) {
					bzero(buf+len+1, sizeof(buf+len+1));
					sendall(i, buf, LENGTH);
					len = 0;
				} else {
           		 	sendall(i, buf, len+1);
				}
				if (len == 0) {
					printf("Write Over\n");
					FD_CLR(i, &masterW);
	  				fclose(qFile);
				}
        	}
		  }
        for (int i = 0; i <= maxfd; i++)
            if (FD_ISSET(i, &readfds)) 
                if (i == sockfd) {
                    if ((newfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) error("ERROR accepting\n");
                    if (fork()) {
                        printf("Conneced\n");
			exit(0);
					} else {
                        if (newfd > maxfd) maxfd = newfd;
						chdir("/home/asy/");
						FD_ZERO(&master);
                        FD_ZERO(&masterW);
                        FD_SET(newfd, &master);
                        FD_SET(newfd, &masterW);
                        flag = true;
                        sum = 0;
                    }
                } else {
                    bzero(buf, sizeof buf);
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        if (nbytes == 0) printf("socket %d hung up with %d left", i, len); else error("ERROR recving\n");
						fclose(pFile);
                        close(i);
						exit(0);
                    } else {
						for (int p = 0; p < nbytes; p++)
							if (len0--) {
                                if (flag) {
                                    name[namelen++] = buf[p]; 
                                    if (len0 == 0) {
										flag = false;
										name[namelen] = '\0';
                                        pFile = fopen(name, "w");
                                    	printf("Created File %s with name length %d\n", name, namelen);
                                    }
                                } else {
                                    fwrite(&buf[p], sizeof(char), 1, pFile);
                                    sum += (double)0.001;
                                }
                            } else {
								len0 = (int)buf[p];
								if (len0==0 && !FD_ISSET(i, &masterW)) { 
									fclose(pFile);
									close(i);
									exit(0);
								}
							}
                        if (sum > pre+1000) {
                            printf("GET %lf MB\n", sum/1000);
                            pre = sum;
                        }
                    }
                }
    }
}
