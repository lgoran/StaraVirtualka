#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "ProtokolNIM.h"
#define N 10
typedef struct
{
	int commSocket;
	char *dekadskiIP;

	int commSocket2;
	char *dekadskiIP2;

	int indexDretve;
	int redIgraca;
} obradiKlijenta__parametar;
obradiKlijenta__parametar parametarDretve[N];
int aktivneDretve[N] = { 0 };
int aktivniIgraci[N] = { 0 };
int brojIgraca=0;
pthread_mutex_t lokot_aktivneDretve = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lokot_2=PTHREAD_MUTEX_INITIALIZER;

int sibice[3]={0,0,0};

void obradi( int sock, int broj_hrpe, char *poruka );
void* komunicirajSaKlijentom( void* parametar )
{
	int vrstaPoruke, gotovo = 0;
	char *poruka;
	obradiKlijenta__parametar *param = (obradiKlijenta__parametar *) parametar;
	int commSocket  = param->commSocket;
	int indexDretve = param->indexDretve;
	
	while( !gotovo )
	{
		if( primiPoruku( commSocket, &vrstaPoruke, &poruka ) != OK )
		{
			if(vrstaPoruke==0)continue;
			printf( "Greska u komunikaciji sa klijentom [socket=%d]...\n", commSocket );
			gotovo = 1;
			continue;
		}
		
		switch( vrstaPoruke )
		{
			case A: obradi( commSocket,0, poruka ); break; 
			case B: obradi( commSocket,1, poruka ); break;
			case C: obradi( commSocket,2, poruka ); break;
			case BOK: posaljiPoruku( commSocket, ODGOVOR, "OK" ); gotovo = 1; break;
			default: posaljiPoruku( commSocket, ODGOVOR, "Nepostojeci kod poruke!\n" );
		}
		pthread_mutex_lock( &lokot_2 );
		aktivneDretve[ indexDretve ] = 2;
		pthread_mutex_unlock( &lokot_2 );
		
		free( poruka );
	}
	printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", param->dekadskiIP, commSocket );
	close(commSocket);
	brojIgraca--;
}
char* int_to_string(int n)
{
	char pom[100];
	int nn,rem,len=0;
	nn = n;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	n = nn;
	char *str=malloc((len+1)*sizeof(char));
	for (int i = 0; i < len; i++)
	{
		rem = n % 10;
		n = n / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
	return str;
}
void izvjestajIgracu(int commSocket)
{
	char pom[100];
		strcpy(pom,int_to_string(brojIgraca));
		strcat(pom,". spojen na server\n");
		strcat(pom,"Hrpa A:");
		strcat(pom,int_to_string(sibice[0]));
		strcat(pom,"  Hrpa B:");
		strcat(pom,int_to_string(sibice[1]));
		strcat(pom,"  Hrpa C:");
		strcat(pom,int_to_string(sibice[2]));

		posaljiPoruku( commSocket, ODGOVOR, pom );
}
int main( int argc, char **argv )
{
	if( argc != 5 )
		error2( "Upotreba: %s port hrpaA hrpaB hrpaC\n", argv[0] );
		
	int port; sscanf( argv[1], "%d", &port );
	sscanf(argv[2],"%d",&sibice[0]);
	sscanf(argv[3],"%d",&sibice[1]);
	sscanf(argv[4],"%d",&sibice[2]);

	// socket...
    int listenerSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( listenerSocket == -1 )
		myperror( "socket" );
		
	// bind...
	struct sockaddr_in mojaAdresa;

	mojaAdresa.sin_family = AF_INET;
	mojaAdresa.sin_port = htons( port );
	mojaAdresa.sin_addr.s_addr = INADDR_ANY;
	memset( mojaAdresa.sin_zero, '\0', 8 );
	
	if( bind( listenerSocket,
		      (struct sockaddr *) &mojaAdresa,
		      sizeof( mojaAdresa ) ) == -1 )
		myperror( "bind" );
		
	// listen
	if( listen( listenerSocket, N*2 ) == -1 )
		myperror( "listen" );
		
	pthread_t dretve[N];
	// accept
	while( 1 )
	{
        struct sockaddr_in klijentAdresa;
		int lenAddr = sizeof( klijentAdresa );

		int commSocket = accept( listenerSocket,
			                     (struct sockaddr *) &klijentAdresa,
			                     &lenAddr );

		if( commSocket == -1 )
			myperror( "accept" );
		brojIgraca++;
		izvjestajIgracu(commSocket);

		char *dekadskiIP = inet_ntoa( klijentAdresa.sin_addr );
		printf( "Prihvatio konekciju od %s [socket=%d]\n", dekadskiIP, commSocket );

		struct sockaddr_in klijentAdresa2;
		int lenAddr2 = sizeof( klijentAdresa2 );

		int commSocket2 = accept( listenerSocket,
			                     (struct sockaddr *) &klijentAdresa2,
			                     &lenAddr2 );

		if( commSocket2 == -1 )
			myperror( "accept" );
		brojIgraca++;
		izvjestajIgracu(commSocket2);

		char *dekadskiIP2 = inet_ntoa( klijentAdresa2.sin_addr );
		printf( "Prihvatio konekciju od %s [socket=%d]\n", dekadskiIP2, commSocket2 );


		pthread_mutex_lock( &lokot_aktivneDretve );
		int i, indexNeaktivne = -1;
		for( i = 0; i < N; ++i )
			if( aktivneDretve[i] == 0 )
				indexNeaktivne = i;
			else if( aktivneDretve[i] == 2 )
			{
				pthread_join( dretve[i], NULL );
				aktivneDretve[i] = 0;
				indexNeaktivne = i;
			}
			    
		if( indexNeaktivne == -1 )
		{
			close( commSocket ); // nemam vise dretvi...
			printf( "--> ipak odbijam konekciju jer nemam vise dretvi.\n" );
		}
		else
		{
		    aktivneDretve[indexNeaktivne] = 1;
			parametarDretve[indexNeaktivne].commSocket = commSocket;
			parametarDretve[indexNeaktivne].indexDretve = indexNeaktivne;
			parametarDretve[indexNeaktivne].dekadskiIP = malloc((sizeof(dekadskiIP)+1)*sizeof(char));
			strcpy(parametarDretve[indexNeaktivne].dekadskiIP,dekadskiIP);
			printf( "--> koristim dretvu broj %d.\n", indexNeaktivne );
			
			pthread_create(
				&dretve[indexNeaktivne], NULL,
				komunicirajSaKlijentom, &parametarDretve[indexNeaktivne] );
		}
		pthread_mutex_unlock( &lokot_aktivneDretve );				
	}
	
	return 0;
}



void obradi( int sock,int broj_hrpe, char *poruka )
{
	int koliko;
	
	if( sscanf( poruka, "%d\n", &koliko ) != 1 || koliko <= 0 )
	{
		posaljiPoruku( sock, ODGOVOR, "Pogresan oblik naredbe" );
		return;
	}
	if(sibice[broj_hrpe]==0)posaljiPoruku( sock, ODGOVOR, "Hrpa je prazna" );
	else if(sibice[broj_hrpe]>=koliko)
	{
		sibice[broj_hrpe]-=koliko;
		char pom[100];
		strcpy(pom,"Na hrpi ");
		char opcija[2];
		opcija[0]='A'+broj_hrpe;
		opcija[1]='\0';
		strcat(pom,opcija);
		strcat(pom," je ostalo jos ");
		strcat(pom,int_to_string(sibice[broj_hrpe]));
		posaljiPoruku( sock, ODGOVOR, pom);
	}
	else posaljiPoruku( sock, ODGOVOR, "Nije moguce dignit toliko sibica" );
}
