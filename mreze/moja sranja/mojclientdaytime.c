/*
	Vjezbe 4 -- Zadatak 1
	daytime-klijent
	Spaja se na IP-adresu proslijedjenu kao prvi argument komandne linije.
	Koristi port proslijedjen kao drugi argument komandne linije.
	
	Npr. za spajanje na daytime server na studentu treba pozvati program sa:
	./daytime-client 161.53.8.14 13
*/

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

int main( int argc, char **argv )
{
	if(argc!=3)
	{
		printf("unos: ./blabla adresa_servera port");
		return 0;
	}
	int mojSocket=socket(PF_INET,SOCK_STREAM,0);
	char dekadskiIP[20];
	int port;
	strcpy(dekadskiIP,argv[1]);
	sscanf(argv[2],"%d",&port);

	struct sockaddr_in adresa_servera;
	adresa_servera.sin_port=htons(port);
	adresa_servera.sin_family=AF_INET;
	if(inet_aton(dekadskiIP,&adresa_servera.sin_addr)==-1)
	 {
		 printf("nevalja adresa inet_aton");
		 return 0;
	 }
	memset(adresa_servera.sin_zero,'\0',8);

	if(connect(mojSocket,(struct sockaddr *)&adresa_servera,sizeof(adresa_servera))==-1)
	{
		printf("sjeba connect");
		return 0;
	}

	char buffer[100];
	int primljeno=0;
	int novoprimljeno=0;

	while (1)
	{
		novoprimljeno=recv(mojSocket,buffer+primljeno,sizeof(buffer)-primljeno-1,0);
		if(novoprimljeno==-1)
		{
			printf("error u primanju");
			return 0;
		}
		else if(novoprimljeno==0)break;
		else primljeno+=novoprimljeno;
	}
	
	printf("%s \n",buffer);
	
	if(close(mojSocket)==-1)
	{
		printf("lose zatvaranje");
		return 0;
	}
	
	return 0;
}
