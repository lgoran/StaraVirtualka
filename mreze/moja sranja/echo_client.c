
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

void posalji(int sock,char* rijec)
{
	int poslano=0;
	int novoposlano=0;
	while (poslano!=sizeof(rijec))
	{
		novoposlano=send(sock,rijec+poslano,sizeof(rijec)-poslano,0);
		if(novoposlano==-1)perror("send");
		else if(novoposlano==0)break;
		else poslano+=novoposlano;
	}
}
void primi(int sock,char* buffer,int duljina_rijeci)
{
	int primljeno=0,novoprimljeno=0;
	while (primljeno!=duljina_rijeci)
	{
		novoprimljeno=recv(sock,buffer+primljeno,sizeof(buffer)-primljeno-1,0);
		if(novoprimljeno==-1)perror("recv");
		else if(novoprimljeno==0)break;
		else primljeno+=novoprimljeno;
	}
	buffer[duljina_rijeci]='\0';
	printf("%s",buffer);
}

int main( int argc, char **argv )
{
	if(argc!=3)perror("argumenti");
	int mojSocket=socket(PF_INET,SOCK_STREAM,0);
	char dekadskiIP[20];
	int port;
	strcpy(dekadskiIP,argv[1]);
	sscanf(argv[2],"%d",&port);
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	if(inet_aton(dekadskiIP,&server.sin_addr)==-1)
		perror("adresa");
	memset(server.sin_zero,'\0',8);

	if(connect(mojSocket,(struct sockaddr *)&server,sizeof(server))==-1)
		perror("connect");
	
	char buffer[100];
	int primljeno=0;
	int novoprimljeno=0;

	while (1)
	{
		char rijec[100],odgovor[100];
		printf("Unesi rijec:\n");
		scanf("%s",rijec);
		if(strcmp(rijec,"kraj"))return 0;
		posalji(mojSocket,rijec);
		primi(mojSocket,odgovor,strlen(rijec));
	}

	close(mojSocket);
	return 0;
}

