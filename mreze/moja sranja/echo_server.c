
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <time.h>

void posalji(int sock,char* buffer,int primljeno)
{
	int poslano=0;
	int novoposlano=0;
	while (poslano!=primljeno)
	{
		novoposlano=send(sock,buffer+poslano,sizeof(buffer)-poslano,0);
		if(novoposlano==-1){perror("send");break;}
		else if(novoposlano==0)break;
		else poslano+=novoposlano;
	}
}
void primi(int sock)
{
	char buffer[5];
	int primljeno=0;
	while (1)
	{
		primljeno=recv(sock,buffer,sizeof(buffer),0);
		if(primljeno==-1){perror("recv");break;}
		else if(primljeno==0){printf("nema vise nista");break;}
		else posalji(sock,buffer,primljeno);
	}
}


int main( int argc, char **argv )
{
	if(argc!=2)perror("argumenti");
	int port;
	sscanf(argv[1],"%d",&port);

	struct sockaddr_in server;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	memset(server.sin_zero,'\0',8);
	
	int listenerSocket=socket(PF_INET,SOCK_STREAM,0);
	if(bind(listenerSocket,(struct sockaddr *)&server,sizeof(server))==-1)perror("bind");
	if(listen(listenerSocket,10)==-1)perror("listen");

	printf("pozz\n");
	char buffer[100];
	while (1)
	{
		struct sockaddr_in klijent;
		int length=sizeof(klijent);
		int communicationSocket=accept(listenerSocket,(struct sockaddr *)&klijent,&length);
		
		if(communicationSocket==-1)perror("accept");
		char *dekadskiIP=inet_ntoa(klijent.sin_addr);
		printf("connect %s\n",dekadskiIP);
		primi(communicationSocket);
		close(communicationSocket);
	}
	return 0;
}

